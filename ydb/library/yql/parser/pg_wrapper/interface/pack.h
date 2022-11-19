#pragma once

#include <ydb/library/yql/public/udf/udf_value.h>

#include <util/generic/buffer.h>
#include <util/generic/strbuf.h>
#include <util/generic/vector.h>

namespace NKikimr {
namespace NMiniKQL {

class TPgType;

void PGPackImpl(bool stable, const TPgType* type, const NUdf::TUnboxedValuePod& value, TBuffer& buf);
NUdf::TUnboxedValue PGUnpackImpl(const TPgType* type, TStringBuf& buf);

void EncodePresortPGValue(TPgType* type, const NUdf::TUnboxedValue& value, TVector<ui8>& output);
NUdf::TUnboxedValue DecodePresortPGValue(TPgType* type, TStringBuf& input, TVector<ui8>& buffer);

ui64 PgValueSize(const TPgType* type, const NUdf::TUnboxedValuePod& value);

} // namespace NMiniKQL
} // namespace NKikimr
