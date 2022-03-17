#include "override_mutator.h"
#include <string.h>
#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <libprotobuf-mutator/port/protobuf.h>
#include <libprotobuf-mutator/src/mutator.h>
#include "main.h"

#define LIB_PROTO_MUTATOR_WEAK_DEF(ReturnType, Name, ...) \
  extern "C" __attribute__((weak)) ReturnType Name(__VA_ARGS__)

LIB_PROTO_MUTATOR_WEAK_DEF(size_t, LLVMFuzzerMutate, uint8_t*, size_t, size_t) {
  return 0;
}

namespace {

template <class T>
T MutateValue(T v) {
  size_t size =
      LLVMFuzzerMutate(reinterpret_cast<uint8_t*>(&v), sizeof(v), sizeof(v));
  memset(reinterpret_cast<uint8_t*>(&v) + size, 0, sizeof(v) - size);
  return v;
}

}  // namespace

int32_t Mutator::MutateInt32(int32_t value) { return MutateValue(value); }

int64_t Mutator::MutateInt64(int64_t value) { return MutateValue(value); }

uint32_t Mutator::MutateUInt32(uint32_t value) { return MutateValue(value); }

uint64_t Mutator::MutateUInt64(uint64_t value) { return MutateValue(value); }

float Mutator::MutateFloat(float value) { return MutateValue(value); }

double Mutator::MutateDouble(double value) { return MutateValue(value); }

std::string Mutator::MutateString(const std::string& value,
                                  int size_increase_hint) {
  // Randomly return empty strings as LLVMFuzzerMutate does not produce them.
  // Use uint16_t because on Windows, uniform_int_distribution does not support
  // any 8 bit types.
  if (!std::uniform_int_distribution<uint16_t>(0, 20)(*random())) return {};
  std::string result = value;
  int new_size = value.size() + size_increase_hint;
  result.resize(std::max(1, new_size));
  result.resize(LLVMFuzzerMutate(reinterpret_cast<uint8_t*>(&result[0]),
                                 value.size(), result.size()));
  return result;
}
