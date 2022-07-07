#ifndef SURVIVOR_SELECTION_OPS_H
#define SURVIVOR_SELECTION_OPS_H

#include "ga_runner.h"

/* Отбор особей в новую популяцию для бинарных строк */

// Метод рулетки
// [double] "survivor_selection_elite_fraction": доля особей, выбираемая элитарным отбором: [0, 1], по умолчанию 0.2
// [double] "survivor_selection_truncate_threshold": доля лучших особей, участвующая в отборе усечением: (0, 1], по умолчанию 0.4
std::vector<BoolString> elite_truncation_survivor_selection_op(GARunner<BoolString>& gar,
											std::vector<BoolString> individuals, 	// комбинация элитарного отбора и отбора усечением
											size_t amount);

#endif
