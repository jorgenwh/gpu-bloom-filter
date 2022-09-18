#include <inttypes.h>

#include <cuda.h>
#include <cuda_runtime.h>

#include "kernels.h"

__global__ void insert_cu_bloom_filter_kernel(
    const uint64_t *keys, const int keyset_size, uint64_t *table, int table_size) 
{
  int key_idx = blockIdx.x * blockDim.x + threadIdx.x;
  uint64_t hash = keys[key_idx] % table_size;

  atomicAdd_system(reinterpret_cast<unsigned long long *>(&table[hash]), 1);
}

void insert_cu_bloom_filter(
    const uint64_t *keys, const int keyset_size, uint64_t *table, int table_size) 
{
  uint32_t num_blocks = keyset_size / THREADS_PER_BLOCK + (keyset_size % THREADS_PER_BLOCK > 0);
  insert_cu_bloom_filter_kernel<<<num_blocks, THREADS_PER_BLOCK>>>(
      keys, keyset_size, table, table_size);
  cudaDeviceSynchronize();
}
