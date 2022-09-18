#include <inttypes.h>
#include <string.h>

#include "cu_bloom_filter.h"
#include "kernels.h"

CuBloomFilter::CuBloomFilter(const int size) {
  size_m = size;
  cudaMalloc(&table_m, sizeof(uint64_t)*size);
  cudaMemset(table_m, 0, sizeof(uint64_t)*size);
}

void CuBloomFilter::insert(const uint64_t *values, const int size) {
  uint64_t *d_values;
  cudaMalloc(&d_values, sizeof(uint64_t)*size);
  cudaMemcpy(d_values, values, sizeof(uint64_t)*size, cudaMemcpyHostToDevice);
  insert_cu_bloom_filter(d_values, size, table_m, size_m);
  cudaFree(d_values);
}

uint64_t CuBloomFilter::get(const uint64_t key) const {
  uint64_t value;
  uint64_t hash = key % size_m;
  cudaMemcpy(&value, &table_m[hash], sizeof(uint64_t), cudaMemcpyDeviceToHost);
  return value;
}
