#ifndef PARENT_SELECTION_OPS_H
#define PARENT_SELECTION_OPS_H

#include "ga_runner.h"

/* Выбор родителей для бинарных строк */

// Метод рулетки
extern double roulette_fitness_influence; 	// влияние значения функции приспособленности на шанс хромосомы быть выбранной в методе рулетки: [0, 1]
std::pair<bool_string, bool_string> roulette_bs_selection_op(std::vector<bool_string> individuals,
																double (*fitness_func)(bool_string));


#endif
