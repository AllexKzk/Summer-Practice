#include "parent_selection_ops.h"
#include <random>

static std::random_device dev_urandom;
static std::mt19937 rng(dev_urandom());

std::pair<BoolString, BoolString> roulette_bs_selection_op(GARunner<BoolString>& gar, std::vector<BoolString> individuals)
{
	double fitness_infl = std::any_cast<double>(gar.get_parameter("roulette_fitness_influence", 0.8));
	double fsum = 0; // сумма всех значений функций приспособленности
	for(size_t i = 0; i < individuals.size(); ++i)
		fsum += gar.fitness_func(gar, individuals[i]);

	BoolString p1, p2; unsigned pcnt = 0;
	std::uniform_real_distribution<double> roulette_dist(0, 1);
	double roll1 = roulette_dist(rng), roll2 = roulette_dist(rng);

	double fcur = 0;
	for(size_t i = 0; i < individuals.size(); ++i){
		double finc = (gar.fitness_func(gar, individuals[i]) / fsum) * fitness_infl + (1. / individuals.size()) * (1 - fitness_infl);
		if(fcur < roll1 && fcur + finc >= roll1) { p1 = individuals[i]; ++pcnt; }
		if(fcur < roll2 && fcur + finc >= roll2) { p2 = individuals[i]; ++pcnt; }
		if(pcnt == 2) break;
		fcur += finc;
	}
	return {p1, p2};
}
