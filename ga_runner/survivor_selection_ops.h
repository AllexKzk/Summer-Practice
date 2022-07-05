#ifndef SURVIVOR_SELECTION_OPS_H
#define SURVIVOR_SELECTION_OPS_H

#include "ga_runner.h"

/* Отбор особей в новую популяцию для бинарных строк */

// Метод рулетки
extern double survivor_selection_elite_fraction;						// доля особей, выбираемая элитарным отбором: [0, 1]
extern double survivor_selection_truncate_threshold;					// доля лучших особей, участвующая в отборе усечением: (0, 1]
std::vector<BoolString> elite_truncation_survivor_selection_op(std::vector<BoolString> individuals, 	// комбинация элитарного отбора и отбора усечением
											size_t amount, double (*fitness_func)(BoolString));

#endif
