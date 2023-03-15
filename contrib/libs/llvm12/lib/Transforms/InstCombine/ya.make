# Generated by devtools/yamaker.

LIBRARY()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm12
    contrib/libs/llvm12/include
    contrib/libs/llvm12/lib/Analysis
    contrib/libs/llvm12/lib/IR
    contrib/libs/llvm12/lib/Support
    contrib/libs/llvm12/lib/Transforms/Utils
)

ADDINCL(
    contrib/libs/llvm12/lib/Transforms/InstCombine
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    InstCombineAddSub.cpp
    InstCombineAndOrXor.cpp
    InstCombineAtomicRMW.cpp
    InstCombineCalls.cpp
    InstCombineCasts.cpp
    InstCombineCompares.cpp
    InstCombineLoadStoreAlloca.cpp
    InstCombineMulDivRem.cpp
    InstCombineNegator.cpp
    InstCombinePHI.cpp
    InstCombineSelect.cpp
    InstCombineShifts.cpp
    InstCombineSimplifyDemanded.cpp
    InstCombineVectorOps.cpp
    InstructionCombining.cpp
)

END()
