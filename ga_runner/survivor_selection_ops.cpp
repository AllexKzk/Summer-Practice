#include "survivor_selection_ops.h"
#include <random>

static std::random_device dev_urandom;
static std::mt19937 rng(dev_urandom());

struct FitnessBsComp
{
	double (*fitness_func)(BoolString);
	FitnessBsComp(double (*fitness_func)(BoolString)) { this->fitness_func = fitness_func; }
	bool operator()(BoolString a, BoolString b) { return fitness_func(a) > fitness_func(b); }
};

double survivor_selection_elite_fraction = 0.2;
double survivor_selection_truncate_threshold = 0.4;
std::vector<BoolString> elite_truncation_survivor_selection_op(std::vector<BoolString> individuals,
											size_t amount, double (*fitness_func)(BoolString))
{
	std::sort(individuals.begin(), individuals.end(), FitnessBsComp(fitness_func));

	size_t elite_amount = ceil(amount * survivor_selection_elite_fraction);
	std::vector<BoolString> new_individuals;
	std::copy(individuals.begin(), individuals.begin() + elite_amount, std::back_inserter(new_individuals));

	size_t trunc_amount = floor(amount * (1 - survivor_selection_elite_fraction));
	size_t trunc_fraction = ceil(amount * survivor_selection_truncate_threshold);

	std::uniform_int_distribution<size_t> trunc_dist(elite_amount, elite_amount + trunc_fraction);
	for(size_t i = 0; i < trunc_amount; ++i)
		new_individuals.push_back(individuals[trunc_dist(rng)]);

	return new_individuals;
}
