#ifndef PERM_GA_H
#define PERM_GA_H

#include "perm_conv.h"
#include "ga_runner/ga_runner.h"

std::vector<BoolString> generate_rand_perms(size_t matrix_size, size_t pop_size);

double perm_fitness_func(GARunner<BoolString> &gar,BoolString bs);

#endif