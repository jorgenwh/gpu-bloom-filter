#include <inttypes.h>
#include <random>
#include <unordered_map>

#include "data_generator.h"

void gen_random_uint64(uint64_t *values, int size) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<unsigned long long> dis(
      std::numeric_limits<uint64_t>::min(),
      std::numeric_limits<uint64_t>::max()
  );

  for (int i = 0; i < size; i++) {
    values[i] = dis(gen);
  }
}

std::unordered_map<uint64_t, uint64_t> get_counts(uint64_t *values, int size) {
  std::unordered_map<uint64_t, uint64_t> map;
  for (int i = 0; i < size; i++) {
    map[values[i]]++;
  }
  return map;
}
