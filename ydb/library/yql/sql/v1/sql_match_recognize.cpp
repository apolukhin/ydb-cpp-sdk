#include "sql_match_recognize.h"
#include "node.h"
#include "sql_expression.h"
namespace NSQLTranslationV1 {

using namespace NSQLv1Generated;

namespace {

TPosition TokenPosition(const TToken& token){
    return TPosition{token.GetColumn(), token.GetLine()};
}

TString PatternVar(const TRule_row_pattern_variable_name& node, TSqlMatchRecognizeClause& ctx){
    return Id(node.GetRule_identifier1(), ctx);
}

} //namespace

TMatchRecognizeBuilderPtr TSqlMatchRecognizeClause::CreateBuilder(const NSQLv1Generated::TRule_row_pattern_recognition_clause &matchRecognizeClause) {
    TPosition pos(matchRecognizeClause.GetToken1().GetColumn(), matchRecognizeClause.GetToken1().GetLine());
    if (!Ctx.FeatureR010) {
        Ctx.Error(pos, TIssuesIds::CORE) << "Unexpected MATCH_RECOGNIZE";
        return {};
    }
    TVector<TPartitioner> partitioners;
    TPosition partitionsPos = pos;
    if (matchRecognizeClause.HasBlock3()) {
        const auto& partitionClause = matchRecognizeClause.GetBlock3().GetRule_window_partition_clause1();
        partitionsPos = TokenPosition(partitionClause.GetToken1());
        partitioners = ParsePartitionBy(partitionClause);
        if (!partitioners)
            return {};
    }
    TVector<TSortSpecificationPtr> sortSpecs;
    TPosition orderByPos = pos;
    if (matchRecognizeClause.HasBlock4()) {
        const auto& orderByClause = matchRecognizeClause.GetBlock4().GetRule_order_by_clause1();
        orderByPos = TokenPosition(orderByClause.GetToken1());
        if (!OrderByClause(orderByClause, sortSpecs)) {
            return {};
        }
    }

    TPosition measuresPos = pos;
    TVector<TNamedLambda> measures;
    if (matchRecognizeClause.HasBlock5()) {
        const auto& measuresClause = matchRecognizeClause.GetBlock5().GetRule_row_pattern_measures1();
        measuresPos = TokenPosition(measuresClause.GetToken1());
        measures = ParseMeasures(measuresClause.GetRule_row_pattern_measure_list2());
    }

    TPosition rowsPerMatchPos = pos;
    ERowsPerMatch rowsPerMatch = ERowsPerMatch::OneRow;
    if (matchRecognizeClause.HasBlock6()) {
        std::tie(rowsPerMatchPos, rowsPerMatch) = ParseRowsPerMatch(matchRecognizeClause.GetBlock6().GetRule_row_pattern_rows_per_match1());
        if (ERowsPerMatch::AllRows == rowsPerMatch) {
            //https://st.yandex-team.ru/YQL-16213
            Ctx.Error(pos, TIssuesIds::CORE) << "ALL ROWS PER MATCH is not supported yet";
            return {};
        }
    }

    const auto& commonSyntax = matchRecognizeClause.GetRule_row_pattern_common_syntax7();

    std::pair<TPosition, TAfterMatchSkipTo> skipTo { pos, TAfterMatchSkipTo{EAfterMatchSkipTo::NextRow, TString()} };
    if (commonSyntax.HasBlock1()){
        skipTo = ParseAfterMatchSkipTo(commonSyntax.GetBlock1().GetRule_row_pattern_skip_to3());
        //TODO validate var with the name defined in the pattern https://st.yandex-team.ru/YQL-16186
    }

    if (commonSyntax.HasBlock2()) {
        const auto& initialOrSeek = commonSyntax.GetBlock2().GetRule_row_pattern_initial_or_seek1();
        Ctx.Error(TokenPosition(initialOrSeek.GetToken1())) << "InitialOrSeek subclause is not allowed in FROM clause";
        return {};
    }

    const auto& pattern = ParsePattern(commonSyntax.GetRule_row_pattern5());
    const auto& patternPos = TokenPosition(commonSyntax.token3());

    TNodePtr subset;
    TPosition subsetPos = pos;
    if (commonSyntax.HasBlock7()) {
        const auto& rowPatternSubset = commonSyntax.GetBlock7().GetRule_row_pattern_subset_clause1();
        subsetPos = TokenPosition(rowPatternSubset.GetToken1());
        Ctx.Error() << "SUBSET is not implemented yet";
        //TODO https://st.yandex-team.ru/YQL-16225
        return {};
    }
    const auto& definitions = ParseDefinitions(commonSyntax.GetRule_row_pattern_definition_list9());
    const auto& definitionsPos = TokenPosition(commonSyntax.GetToken8());

    return new TMatchRecognizeBuilder{
        pos,
        std::pair{partitionsPos, std::move(partitioners)},
        std::pair{orderByPos, std::move(sortSpecs)},
        std::pair{measuresPos, measures},
        std::pair{rowsPerMatchPos, rowsPerMatch},
        std::move(skipTo),
        std::pair{patternPos, std::move(pattern)},
        std::pair{subsetPos, std::move(subset)},
        std::pair{definitionsPos, std::move(definitions)}
    };


}

TVector<TPartitioner> TSqlMatchRecognizeClause::ParsePartitionBy(const TRule_window_partition_clause& partitionClause) {
    TColumnRefScope scope(Ctx, EColumnRefState::Allow);
    TVector<TNodePtr> partitionExprs;
    if (!NamedExprList(
            partitionClause.GetRule_named_expr_list4(),
            partitionExprs)) {
        return {};
    }
    TVector<TPartitioner> partitioners;
    for (const auto& p: partitionExprs) {
        auto label = p->GetLabel();
        if (!label && p->GetColumnName()) {
            label = *p->GetColumnName();
        }
        partitioners.push_back(TPartitioner{p, label});
    }
    return partitioners;
}

TNamedLambda TSqlMatchRecognizeClause::ParseOneMeasure(const TRule_row_pattern_measure_definition& node) {
    TColumnRefScope scope(Ctx, EColumnRefState::Allow);
    const auto& expr = TSqlExpression(Ctx, Mode).Build(node.GetRule_expr1());
    const auto& name = Id(node.GetRule_an_id3(), *this);
    //TODO https://st.yandex-team.ru/YQL-16186
    //Each measure must be a lambda, that accepts 2 args:
    // - List<InputTableColumns + _yql_Classifier, _yql_MatchNumber, _yqlMatchRowNumber>
    // - Struct that maps row pattern variables to ranges in the queue
    return {expr, name};
}

TVector<TNamedLambda> TSqlMatchRecognizeClause::ParseMeasures(const TRule_row_pattern_measure_list& node) {
    TVector<TNamedLambda> result{ ParseOneMeasure(node.GetRule_row_pattern_measure_definition1()) };
    for (const auto& m: node.GetBlock2()) {
        result.push_back(ParseOneMeasure(m.GetRule_row_pattern_measure_definition2()));
    }
    return result;
}

std::pair<TPosition, ERowsPerMatch> TSqlMatchRecognizeClause::ParseRowsPerMatch(const TRule_row_pattern_rows_per_match& rowsPerMatchClause) {

    switch(rowsPerMatchClause.GetAltCase()) {
        case TRule_row_pattern_rows_per_match::kAltRowPatternRowsPerMatch1:
            return std::pair {
                    TokenPosition(rowsPerMatchClause.GetAlt_row_pattern_rows_per_match1().GetToken1()),
                    ERowsPerMatch::OneRow
            };
        case TRule_row_pattern_rows_per_match::kAltRowPatternRowsPerMatch2:
            return std::pair {
                    TokenPosition(rowsPerMatchClause.GetAlt_row_pattern_rows_per_match2().GetToken1()),
                    ERowsPerMatch::AllRows
            };
        case TRule_row_pattern_rows_per_match::ALT_NOT_SET:
            Y_FAIL("You should change implementation according to grammar changes");
    }
}

std::pair<TPosition, TAfterMatchSkipTo> TSqlMatchRecognizeClause::ParseAfterMatchSkipTo(const TRule_row_pattern_skip_to& skipToClause) {
    switch (skipToClause.GetAltCase()) {
        case TRule_row_pattern_skip_to::kAltRowPatternSkipTo1:
            return std::pair{
                    TokenPosition(skipToClause.GetAlt_row_pattern_skip_to1().GetToken1()),
                    TAfterMatchSkipTo{EAfterMatchSkipTo::NextRow}
            };
        case TRule_row_pattern_skip_to::kAltRowPatternSkipTo2:
            return std::pair{
                    TokenPosition(skipToClause.GetAlt_row_pattern_skip_to2().GetToken1()),
                    TAfterMatchSkipTo{EAfterMatchSkipTo::PastLastRow}
            };
        case TRule_row_pattern_skip_to::kAltRowPatternSkipTo3:
            return std::pair{
                    TokenPosition(skipToClause.GetAlt_row_pattern_skip_to3().GetToken1()),
                    TAfterMatchSkipTo{
                            EAfterMatchSkipTo::ToFirst,
                            skipToClause.GetAlt_row_pattern_skip_to3().GetToken1().GetValue()
                    }
            };
        case TRule_row_pattern_skip_to::kAltRowPatternSkipTo4:
            return std::pair{
                    TokenPosition(skipToClause.GetAlt_row_pattern_skip_to4().GetToken1()),
                    TAfterMatchSkipTo{
                            EAfterMatchSkipTo::ToLast,
                            skipToClause.GetAlt_row_pattern_skip_to4().GetToken1().GetValue()
                    }
            };
        case TRule_row_pattern_skip_to::kAltRowPatternSkipTo5:
            return std::pair{
                    TokenPosition(skipToClause.GetAlt_row_pattern_skip_to5().GetToken1()),
                    TAfterMatchSkipTo{
                            EAfterMatchSkipTo::To,
                            skipToClause.GetAlt_row_pattern_skip_to5().GetToken1().GetValue()
                    }
            };
        case TRule_row_pattern_skip_to::ALT_NOT_SET:
            Y_FAIL("You should change implementation according to grammar changes");
    }
}

TRowPatternTerm TSqlMatchRecognizeClause::ParsePatternTerm(const TRule_row_pattern_term& node){
    TRowPatternTerm term;
    TPosition pos;
    for (const auto& factor: node.GetBlock1()) {
        const auto& primaryVar = factor.GetRule_row_pattern_factor1().GetRule_row_pattern_primary1();
        TString varName;
        bool output = true;
        switch(primaryVar.GetAltCase()){
            case TRule_row_pattern_primary::kAltRowPatternPrimary1:
                varName = PatternVar(primaryVar.GetAlt_row_pattern_primary1().GetRule_row_pattern_primary_variable_name1().GetRule_row_pattern_variable_name1(), *this);
                break;
            case TRule_row_pattern_primary::kAltRowPatternPrimary2:
                varName = primaryVar.GetAlt_row_pattern_primary2().GetToken1().GetValue();
                Y_ENSURE("$" == varName);
                break;
            case TRule_row_pattern_primary::kAltRowPatternPrimary3:
                varName = primaryVar.GetAlt_row_pattern_primary3().GetToken1().GetValue();
                Y_ENSURE("^" == varName);
                break;
            case TRule_row_pattern_primary::kAltRowPatternPrimary4:
                Ctx.Error(TokenPosition(primaryVar.GetAlt_row_pattern_primary4().GetToken1()))
                    << "Grouping is not supported yet"; //https://st.yandex-team.ru/YQL-16226
                break;
            case TRule_row_pattern_primary::kAltRowPatternPrimary5:
                output = false;
                Ctx.Error(TokenPosition(primaryVar.GetAlt_row_pattern_primary4().GetToken1()))
                        << "ALL ROWS PER MATCH and {- -} are not supported yet"; //https://st.yandex-team.ru/YQL-16227
                break;
            case TRule_row_pattern_primary::kAltRowPatternPrimary6:
                Ctx.Error(TokenPosition(primaryVar.GetAlt_row_pattern_primary4().GetToken1()))
                        << "PERMUTE is not supported yet"; //https://st.yandex-team.ru/YQL-16228
                break;
            case TRule_row_pattern_primary::ALT_NOT_SET:
                Y_FAIL("You should change implementation according to grammar changes");
        }
        uint64_t quantityMin = 1;
        uint64_t quantityMax = 1;
        constexpr uint64_t infinity = std::numeric_limits<uint64_t>::max();
        bool greedy = true;
        if (factor.GetRule_row_pattern_factor1().HasBlock2()) {
            const auto& quantifier = factor.GetRule_row_pattern_factor1().GetBlock2().GetRule_row_pattern_quantifier1();
            switch(quantifier.GetAltCase()){
                case TRule_row_pattern_quantifier::kAltRowPatternQuantifier1: //*
                    quantityMin = 0;
                    quantityMax = infinity;
                    greedy = !quantifier.GetAlt_row_pattern_quantifier1().HasBlock2();
                    break;
                case TRule_row_pattern_quantifier::kAltRowPatternQuantifier2: //+
                    quantityMax = infinity;
                    greedy = !quantifier.GetAlt_row_pattern_quantifier2().HasBlock2();
                    break;
                case TRule_row_pattern_quantifier::kAltRowPatternQuantifier3: //?
                    quantityMin = 0;
                    greedy = !quantifier.GetAlt_row_pattern_quantifier3().HasBlock2();
                    break;
                case TRule_row_pattern_quantifier::kAltRowPatternQuantifier4: //{ 2?, 4?}
                    if (quantifier.GetAlt_row_pattern_quantifier4().HasBlock2()) {
                        quantityMin = FromString(quantifier.GetAlt_row_pattern_quantifier4().GetBlock2().GetRule_integer1().GetToken1().GetValue());
                    }
                    else {
                        quantityMin = 0;;
                    }
                    if (quantifier.GetAlt_row_pattern_quantifier4().HasBlock4()) {
                        quantityMax = FromString(quantifier.GetAlt_row_pattern_quantifier4().GetBlock4().GetRule_integer1().GetToken1().GetValue());
                    }
                    else {
                        quantityMax = infinity;
                    }
                    greedy = !quantifier.GetAlt_row_pattern_quantifier4().HasBlock6();

                    break;
                case TRule_row_pattern_quantifier::kAltRowPatternQuantifier5:
                    quantityMin = quantityMax = FromString(quantifier.GetAlt_row_pattern_quantifier5().GetRule_integer2().GetToken1().GetValue());
                    break;
                case TRule_row_pattern_quantifier::ALT_NOT_SET:
                    Y_FAIL("You should change implementation according to grammar changes");
            }
        }
        term.push_back(TRowPatternFactor{varName, quantityMin, quantityMax, greedy, output});
    }
    return term;
}

TVector<TRowPatternTerm> TSqlMatchRecognizeClause::ParsePattern(const TRule_row_pattern& node){
    TVector<TRowPatternTerm> result{ ParsePatternTerm(node.GetRule_row_pattern_term1()) };
    for (const auto& term: node.GetBlock2())
        result.push_back(ParsePatternTerm(term.GetRule_row_pattern_term2()));
    return result;
}

TNamedLambda TSqlMatchRecognizeClause::ParseOneDefinition(const TRule_row_pattern_definition& node){
    const auto& varName = PatternVar(node.GetRule_row_pattern_definition_variable_name1().GetRule_row_pattern_variable_name1(), *this);
    TColumnRefScope scope(Ctx, EColumnRefState::Allow);
    const auto& searchCondition = TSqlExpression(Ctx, Mode).Build(node.GetRule_row_pattern_definition_search_condition3().GetRule_search_condition1().GetRule_expr1());
    return TNamedLambda{searchCondition, varName};
}

TVector<TNamedLambda> TSqlMatchRecognizeClause::ParseDefinitions(const TRule_row_pattern_definition_list& node) {
    TVector<TNamedLambda> result { ParseOneDefinition(node.GetRule_row_pattern_definition1())};
    for (const auto& d: node.GetBlock2()) {
        //TODO https://st.yandex-team.ru/YQL-16186
        //Each define must be a predicate lambda, that accepts 3 args:
        // - List<input table rows>
        // - A struct that maps row pattern variables to ranges in the queue
        // - An index of the current row
        result.push_back(ParseOneDefinition(d.GetRule_row_pattern_definition2()));
    }
    return result;
}

} //namespace NSQLTranslationV1
