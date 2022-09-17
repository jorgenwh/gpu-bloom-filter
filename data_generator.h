#ifndef DATA_GENERATOR_H_
#define DATA_GENERATOR_H_

#include <inttypes.h>
#include <random>
#include <unordered_map>

void gen_random_uint64(uint64_t *values, int size);
std::unordered_map<uint64_t, uint64_t> get_counts(uint64_t *values, int size);

#endif // DATA_GENERATOR_H_
