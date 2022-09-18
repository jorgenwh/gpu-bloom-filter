#include <iostream>
#include <inttypes.h>
#include <chrono>
#include <unordered_map>

#include "bloom_filter.h"
#include "cu_bloom_filter.h"
#include "data_generator.h"

int main(int argc, char **argv) {
  int size = 100000;
  int bf_size = size*10;
  std::cout << "keyset size: " << size << ", filter size: " << bf_size << "\n";

  uint64_t *values = new uint64_t[size];
  gen_random_uint64(values, size);
  std::unordered_map<uint64_t, uint64_t> counts = get_counts(values, size);

  BloomFilter bloom_filter(bf_size);
  CuBloomFilter cu_bloom_filter(bf_size);

  auto t1 = std::chrono::high_resolution_clock::now();
  bloom_filter.insert(values, size);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
  std::cout << "Time elapsed to insert " << size << " elements (CPU): " << elapsed << " ns\n";

  t1 = std::chrono::high_resolution_clock::now();
  cu_bloom_filter.insert(values, size);
  t2 = std::chrono::high_resolution_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
  std::cout << "Time elapsed to insert " << size << " elements (GPU): " << elapsed << " ns\n";

  int n = 0;
  int fp = 0;
  int cu_fp = 0;
  for (auto &e : counts) {
    uint64_t key = e.first;
    uint64_t correct_count = e.second;
    uint64_t bloom_count = bloom_filter.get(key);
    uint64_t cu_bloom_count = cu_bloom_filter.get(key);

    n++;
    fp += (int)(correct_count != bloom_count);
    cu_fp += (int)(correct_count != cu_bloom_count);

    if (bloom_count != cu_bloom_count) {
      std::cout << "CPU and GPU bloom count differ\n";
    }

    /*std::cout 
      << "key=" << key 
      << ", count=" << correct_count 
      << ", bfcount=" << bloom_count 
      << ", cubfcount=" << cu_bloom_count 
      << "\n";*/
  }

  std::cout << "false positives: " << ((double)(double)fp / (double)n) << "\n";
  printf("%f\n", ((double)fp) / ((double)n));

  std::cout << "cu false positives: " << ((double)(double)cu_fp / (double)n) << "\n";
  printf("%f\n", ((double)cu_fp) / ((double)n));

  delete[] values;

  return 0;
}
