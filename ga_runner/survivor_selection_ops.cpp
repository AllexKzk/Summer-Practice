#include "survivor_selection_ops.h"
#include <algorithm>
#include <random>

static std::random_device dev_urandom;
static std::mt19937 rng(dev_urandom());

struct FitnessBsComp
{
	GARunner<BoolString>& gar;
	FitnessBsComp(GARunner<BoolString>& gar) : gar(gar){};
	bool operator()(BoolString a, BoolString b) { return gar.fitness_func(gar, a) > gar.fitness_func(gar, b); }
};

std::vector<BoolString> elite_truncation_survivor_selection_op(GARunner<BoolString>& gar, std::vector<BoolString> individuals,
											size_t amount)
{
	double elite_frac = std::any_cast<double>(gar.get_parameter("density_mutation_chance", 0.2));
	double trunc_thres = std::any_cast<double>(gar.get_parameter("survivor_selection_truncate_threshold", 0.4));
	std::sort(individuals.begin(), individuals.end(), FitnessBsComp(gar));

	size_t elite_amount = ceil(amount * elite_frac);
	std::vector<BoolString> new_individuals;
	std::copy(individuals.begin(), individuals.begin() + elite_amount, std::back_inserter(new_individuals));

	size_t trunc_amount = floor(amount * (1 - elite_frac));
	size_t trunc_fraction = ceil(amount * trunc_thres);

	std::uniform_int_distribution<size_t> trunc_dist(elite_amount, elite_amount + trunc_fraction);
	for(size_t i = 0; i < trunc_amount; ++i)
		new_individuals.push_back(individuals[trunc_dist(rng)]);

	return new_individuals;
}
