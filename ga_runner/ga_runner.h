#ifndef GA_RUNNER_H
#define GA_RUNNER_H

#include <iostream>
#include <vector>
#include <random>
#include <pthread.h>

#include "bool_string.h"

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

		void print_data(std::vector<data> wh)
		{
			for(size_t i = 0; i < wh.size(); ++i){
				std::cout << wh[i] << ' ';
			}
			std::cout << '\n';
		}

		pthread_t work_thread;

		pthread_mutex_t thread_mode_mutex;
		enum {
			GATerminated,
			GADoNIterations,
			GADoUntilNoChildren
		} thread_mode;
		size_t iter_counter;

		friend void* thread_iteration(void* _args);
		static void* thread_iteration(void* _args)
		{
			GARunner* self = (GARunner*)_args;
			size_t prev_children = 1;
			while(1){
				pthread_mutex_lock(&self->thread_mode_mutex);
				switch(self->thread_mode){
					case GATerminated: goto terminate;
					case GADoNIterations: if(self->iter_counter == 0) goto terminate; else --self->iter_counter; break;
					case GADoUntilNoChildren: if(prev_children == 0) goto terminate; break;
				}
				pthread_mutex_unlock(&self->thread_mode_mutex);
				prev_children = self->do_iteration();
			}
			terminate:
			self->thread_mode = GATerminated;
			pthread_mutex_unlock(&self->thread_mode_mutex);
			return NULL;
		}


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
		fitness_func(fitness_func), recombination_op(recombination_op), mutation_op(mutation_op), parent_selection_op(parent_selection_op), survivor_selection_op(survivor_selection_op)
		{
			thread_mode = GATerminated;
			iter_counter = 0;
			pthread_mutex_init(&thread_mode_mutex, NULL);
		}

		size_t do_iteration()
		{
			std::vector<data> children;
			for(size_t i = 0; i <= population_size; i += 2){
				// отбираем двух родителей
				std::pair<data, data> parents = parent_selection_op(current_population, fitness_func);
				std::cout << "parents: "; print_data({parents.first, parents.second});
				if(parents.first != parents.second){
					std::vector<data> more_children = recombination_op(parents.first, parents.second); // проводим скрещивание
					std::copy(more_children.begin(), more_children.end(), std::back_inserter(children));
				}
			}
			std::cout << "children: "; print_data(children);

			std::mt19937 rng(dev_urandom());
			std::uniform_real_distribution<double> mutation_dist(0, 1);
			for(size_t i = 0; i < children.size(); ++i)
				if(mutation_dist(rng) < mutation_chance)
					children[i] = mutation_op(children[i]);	// производим мутацию с заданным шансом
			std::cout << "mutated children: "; print_data(children);

			// заносим детей и родителей в один список и отбираем оттуда особей для следующей популяции
			std::copy(children.begin(), children.end(), std::back_inserter(current_population));
			current_population = survivor_selection_op(current_population, population_size, fitness_func);

			std::cout << "current population: "; print_data(current_population);

			return children.size();
		}

		void thread_terminate()
		{
			pthread_mutex_lock(&thread_mode_mutex);
			thread_mode = GATerminated;
			pthread_mutex_unlock(&thread_mode_mutex);
			pthread_join(work_thread, NULL);
		}
		void thread_iterate_count(size_t count)
		{
			bool create_thread = (thread_mode == GATerminated);
			pthread_mutex_lock(&thread_mode_mutex);
			iter_counter = count;
			thread_mode = GADoNIterations;
			pthread_mutex_unlock(&thread_mode_mutex);
			if(create_thread)
				pthread_create(&work_thread, NULL, GARunner::thread_iteration, (void*)this);
		}
		void thread_iterate_until_no_children()
		{
			bool create_thread = (thread_mode == GATerminated);
			pthread_mutex_lock(&thread_mode_mutex);
			thread_mode = GADoUntilNoChildren;
			pthread_mutex_unlock(&thread_mode_mutex);
			if(create_thread)
				pthread_create(&work_thread, NULL, GARunner::thread_iteration, (void*)this);
		}

		void print_current_population() { print_data(current_population); }
};

#endif
