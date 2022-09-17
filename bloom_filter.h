#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

#include <inttypes.h>

class BloomFilter {
public:
  BloomFilter() = default;
  BloomFilter(int size);
  ~BloomFilter() { delete[] table_m; }

  void insert(uint64_t *values, int size);
  uint64_t get(uint64_t key);
private:
  int size_m;
  uint64_t *table_m;
};

#endif // BLOOM_FILTER_H_
