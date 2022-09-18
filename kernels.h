#ifndef KERNELS_H_
#define KERNELS_H_

#include <inttypes.h>

#include <cuda.h>
#include <cuda_runtime.h>

#define THREADS_PER_BLOCK 1024

void insert_cu_bloom_filter(
    const uint64_t *keys, const int keyset_size, uint64_t *table, int table_size);

#endif // KERNELS_H_
