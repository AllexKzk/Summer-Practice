#ifndef MUTATION_OPS_H
#define MUTATION_OPS_H

#include "ga_runner.h"

/* Мутация бинарных строк */

// Мутация с использованием понятия плотности
// [double] "density_mutation_chance": шанс мутации (инверсии) каждого гена: [0; 1], по умолчанию 0.01
BoolString density_mutation_op(GARunner<BoolString>& gar, BoolString bs);


#endif
