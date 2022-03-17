#include "honggfuzz.h"

#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

    void MutateCall(run_t* run, uint64_t Seed);

#ifdef __cplusplus
}
#endif

size_t FuzzerMutate(uint8_t *Data, size_t Size, size_t MaxSize);
