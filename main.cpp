#include <iostream>
#include <inttypes.h>
#include <unordered_map>

#include "bloom_filter.h"
#include "data_generator.h"

int main(int argc, char **argv) {
  int size = 10000;
  int bloom_filter_size = size*1000;
  uint64_t *values = new uint64_t[size];
  gen_random_uint64(values, size);
  std::unordered_map<uint64_t, uint64_t> counts = get_counts(values, size);

  BloomFilter bloom_filter(bloom_filter_size);
  bloom_filter.insert(values, size);

  int n = 0;
  int fp = 0;
  for (auto &e : counts) {
    uint64_t key = e.first;
    uint64_t correct_count = e.second;
    uint64_t bloom_count = bloom_filter.get(key);

    n++;
    fp += (int)(correct_count != bloom_count);

    /*std::cout 
      << "key=" << key 
      << ", count=" << correct_count 
      << ", bfcount=" << bloom_count 
      << "\n";*/
  }

  std::cout << "false positives: " << ((double)(double)fp / (double)n) << "\n";
  printf("%f\n", ((double)fp) / ((double)n));

  delete[] values;

  return 0;
}
