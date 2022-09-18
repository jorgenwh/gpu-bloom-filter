#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

#include <inttypes.h>

class BloomFilter {
public:
  BloomFilter() = default;
  BloomFilter(const int size);
  ~BloomFilter() { delete[] table_m; }

  void insert(const uint64_t *values, const int size);
  uint64_t get(const uint64_t key) const;
private:
  int size_m;
  uint64_t *table_m;
};

#endif // BLOOM_FILTER_H_
