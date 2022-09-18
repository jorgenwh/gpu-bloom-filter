#ifndef CU_BLOOM_FILTER_H_
#define CU_BLOOM_FILTER_H_

#include <inttypes.h>

#include <cuda.h>
#include <cuda_runtime.h>

#include "kernels.h"

class CuBloomFilter {
public:
  CuBloomFilter() = default;
  CuBloomFilter(const int size);
  ~CuBloomFilter() { cudaFree(table_m); }

  void insert(const uint64_t *values, const int size);
  uint64_t get(const uint64_t key) const;
private:
  int size_m;
  uint64_t *table_m;
};

#endif // CU_BLOOM_FILTER_H_
