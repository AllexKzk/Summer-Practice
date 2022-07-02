#ifndef GA_RUNNER_H
#define GA_RUNNER_H

#include <iostream>
#include <vector>
#include <random>

#include "ga_op.h"

typedef std::vector<bool> bool_string;

/* data - тип данных, используемых в ГА (хромосом). Предопределённые функции работают в основном с double или bool_string (std::vector<bool>).
*  fitness_func - функция приспособленности. Чем больше значение, тем больше приспособленность (знак учитывается).
*  recombination_op - оператор рекомбинации. Возвращает одного или несколько потомков двух родителей. Предполагается, что количество генов в обоих родителях совпадает (в большинстве видов такого оператора).
*  mutation_op - оператор мутации. Возвращает модифицированную хромосому.
*  parent_selection_op - оператор выбора родителей. Выбор производится из поданного на вход списка особей.
*  survivor_selection_op - оператор отбора в новую популяцию. Напрямую модифицирует поданный на вход вектор.
*/
template<typename data>
class GARunner
{
	private:
		size_t population_size;
		std::vector<data> current_population;

		double mutation_chance;
		double (*fitness_func)(data);

		std::vector<data> (*recombination_op)(data, data);
		data (*mutation_op)(data);
		std::pair<data, data> (*parent_selection_op)(std::vector<data>, double (*fitness_func_arg)(data));
		std::vector<data> (*survivor_selection_op)(std::vector<data>, size_t amount, double (*fitness_func_arg)(data));

		std::random_device dev_urandom;

	public:
		std::vector<data>& get_current_population() { return current_population; }

		GARunner(size_t population_size, std::vector<data> initial_population,
			double mutation_chance,
			double (*fitness_func)(data),
			std::vector<data> (*recombination_op)(data, data),
			data (*mutation_op)(data),
			std::pair<data, data> (*parent_selection_op)(std::vector<data>, double (*fitness_func_arg)(data)),
			std::vector<data> survivor_selection_op(std::vector<data>, size_t amount, double (*fitness_func_arg)(data)))
		: population_size(population_size), current_population(initial_population), mutation_chance(mutation_chance),
		fitness_func(fitness_func), recombination_op(recombination_op), mutation_op(mutation_op), parent_selection_op(parent_selection_op), survivor_selection_op(survivor_selection_op){}

		void do_iteration()
		{
			std::vector<data> children;
			for(size_t i = 0; i <= population_size; i += 2){
				// отбираем двух родителей
				std::pair<data, data> parents = parent_selection_op(current_population, fitness_func);
				std::cout << "parents: "; print_test({parents.first, parents.second});
				if(parents.first != parents.second){
					std::vector<data> more_children = recombination_op(parents.first, parents.second); // проводим скрещивание
					std::copy(more_children.begin(), more_children.end(), std::back_inserter(children));
				}
			}
			std::cout << "children: "; print_test(children);

			std::mt19937 rng(dev_urandom());
			std::uniform_real_distribution<double> mutation_dist(0, 1);
			for(size_t i = 0; i < children.size(); ++i)
				if(mutation_dist(rng) < mutation_chance)
					children[i] = mutation_op(children[i]);	// производим мутацию с заданным шансом
			std::cout << "mutated children: "; print_test(children);

			// заносим детей и родителей в один список и отбираем оттуда особей для следующей популяции
			std::copy(children.begin(), children.end(), std::back_inserter(current_population));
			current_population = survivor_selection_op(current_population, population_size, fitness_func);

			std::cout << "current population: "; print_test(current_population);
		}

		void print_test(std::vector<data> wh)
		{
			for(size_t i = 0; i < wh.size(); ++i){
				for(size_t j = 0; j < wh[i].size(); ++j)
					std::cout << (int)wh[i][j];
				std::cout << ' ';
			}
			std::cout << '\n';
		}
};

#endif
