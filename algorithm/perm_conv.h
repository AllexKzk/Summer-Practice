#ifndef PERM_CONV_H
#define PERM_CONV_H

#include "ga_runner/bool_string.h"
#include "permutation.h"

BoolString perm_to_bool_string(Permutation p);
Permutation bool_string_to_perm(BoolString bs, size_t matrix_size);

#endif
