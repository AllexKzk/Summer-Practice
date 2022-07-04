#include "mutation_ops.h"
#include <random>

static std::random_device dev_urandom;
static std::mt19937 rng(dev_urandom());

double density_mutation_chance = 0.01;
BoolString density_mutation_op(BoolString bs)
{
	BoolString _out = bs;
	std::uniform_real_distribution<double> mut_dist(0, 1);
	for(size_t i = 0; i < bs.size(); ++i){
		if(mut_dist(rng) <= density_mutation_chance)
			_out[i] = !_out[i];
	}
	return _out;
}
