#include <bits/stdc++.h>
#include <algorithm>
#include <memory>
#include <vector>
#include "test.pb.h"
#include "honggfuzz.h"


struct Handle
{
    uint8_t*    stream;
    size_t      MaxSize;
    size_t      FileSize;
    uint64_t    Seed;
};

std::string Mutate_Serialize(uint8_t* stream);
void Mutate_DeSerialize(Handle* handle, std::string data);

