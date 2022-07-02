#ifndef RECOMBINATION_OPS
#define RECOMBINATION_OPS

#include "ga_runner.h"

/* Бинарная рекомбинация (кроссинговер) */

// Количество точек равно ceil(ln(N)), где N - количество бит в двоичных строках
std::vector<bool_string> multi_point_crossingover(bool_string bs1, bool_string bs2);

#endif
