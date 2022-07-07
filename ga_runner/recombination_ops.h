#ifndef RECOMBINATION_OPS
#define RECOMBINATION_OPS

#include "ga_runner.h"

/* Бинарная рекомбинация (кроссинговер) */

// Количество точек равно ceil(ln(N)), где N - количество бит в двоичных строках
std::vector<BoolString> multi_point_crossingover(GARunner<BoolString>& gar, BoolString bs1, BoolString bs2);

#endif
