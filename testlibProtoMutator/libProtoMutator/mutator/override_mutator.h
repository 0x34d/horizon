#include <string.h>
#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <libprotobuf-mutator/src/mutator.h>

//class Mutator : public protobuf_mutator::Mutator { /*...*/    };

class Mutator : public protobuf_mutator::Mutator {
 public:
  using protobuf_mutator::Mutator::Mutator;

 protected:
  int32_t MutateInt32(int32_t value) override;
  int64_t MutateInt64(int64_t value) override;
  uint32_t MutateUInt32(uint32_t value) override;
  uint64_t MutateUInt64(uint64_t value) override;
  float MutateFloat(float value) override;
  double MutateDouble(double value) override;
  std::string MutateString(const std::string& value,
                           int size_increase_hint) override;
};