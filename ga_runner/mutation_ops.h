#ifndef MUTATION_OPS_H
#define MUTATION_OPS_H

#include "ga_runner.h"

/* Мутация бинарных строк */

// Мутация с использованием понятия плотности
extern double density_mutation_chance;	// шанс мутации (инверсии) каждого гена: [0; 1], по умолчанию 0.01
bool_string density_mutation_op(bool_string bs);


#endif
