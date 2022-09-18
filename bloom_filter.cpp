#include <inttypes.h>
#include <string.h>

#include "bloom_filter.h"

BloomFilter::BloomFilter(const int size) {
  size_m = size;
  table_m = new uint64_t[size];
  memset(table_m, 0, sizeof(uint64_t)*size);
}

void BloomFilter::insert(const uint64_t *values, const int size) {
  for (int i = 0; i < size; i++) {
    uint64_t hash = values[i] % size_m;
    table_m[hash]++;
  }
}

uint64_t BloomFilter::get(const uint64_t key) const {
  uint64_t hash = key % size_m;
  return table_m[hash];
}
