#ifndef PARENT_SELECTION_OPS_H
#define PARENT_SELECTION_OPS_H

#include "ga_runner.h"

/* Выбор родителей для бинарных строк */

// Метод рулетки
extern double roulette_fitness_influence; 	// влияние значения функции приспособленности на шанс хромосомы быть выбранной в методе рулетки: [0, 1]
std::pair<BoolString, BoolString> roulette_bs_selection_op(std::vector<BoolString> individuals,
																double (*fitness_func)(BoolString));


#endif
