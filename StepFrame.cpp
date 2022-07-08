#include "StepFrame.h"

#include <iostream>

#include "algorithm/perm_ga.h"
#include "algorithm/perm_conv.h"
#include "ga_runner/recombination_ops.h"
#include "ga_runner/mutation_ops.h"
#include "ga_runner/parent_selection_ops.h"
#include "ga_runner/survivor_selection_ops.h"

static void GACBIterationStart(GARunner<BoolString>& gar, std::vector<BoolString> pop)
{
	StepFrame* self = std::any_cast<StepFrame*>(gar.get_parameter("step_frame", nullptr));
	self->crossingOver.clear();
	self->initPopulation.clear();
	self->mutations.clear();
	self->newPopulation.clear();
	self->bestObj.clear();

	size_t mat_size = std::any_cast<std::vector<std::vector<double>>>(gar.get_parameter("cost_matrix", {})).size();
	for(auto i = pop.begin(); i != pop.end(); ++i){
		std::stringstream obj, fit;
		obj << bool_string_to_perm(*i, mat_size);
		fit << gar.fitness_func(gar, *i);
		self->initPopulation.addRow(obj.str(), fit.str());
	}
}
static void GACBNewChildren(GARunner<BoolString>& gar, std::pair<BoolString, BoolString> parents, std::vector<BoolString> children)
{
	StepFrame* self = std::any_cast<StepFrame*>(gar.get_parameter("step_frame", nullptr));
	size_t mat_size = std::any_cast<std::vector<std::vector<double>>>(gar.get_parameter("cost_matrix", {})).size();

	std::stringstream parents_str, children_str;
	parents_str << bool_string_to_perm(parents.first, mat_size) << " " << bool_string_to_perm(parents.second, mat_size);
	for(auto i = children.begin(); i != children.end(); ++i)
		children_str << bool_string_to_perm(*i, mat_size) << ' ';
	self->crossingOver.addRow(parents_str.str(), children_str.str());
}
static void GACBMutation(GARunner<BoolString>& gar, std::vector<BoolString> old_children, std::vector<BoolString> new_children)
{
	StepFrame* self = std::any_cast<StepFrame*>(gar.get_parameter("step_frame", nullptr));
	size_t mat_size = std::any_cast<std::vector<std::vector<double>>>(gar.get_parameter("cost_matrix", {})).size();

	for(auto i = old_children.begin(), j = new_children.begin(); i != old_children.end(); ++i, ++j){
		std::stringstream before_mut, after_mut;
		before_mut << bool_string_to_perm(*i, mat_size);
		after_mut << bool_string_to_perm(*j, mat_size);
		if(before_mut.str() != after_mut.str())
		self->mutations.addRow(before_mut.str(), after_mut.str());
	}
}
static void GACBNewPopulation(GARunner<BoolString>& gar, std::vector<BoolString> pop)
{
	StepFrame* self = std::any_cast<StepFrame*>(gar.get_parameter("step_frame", nullptr));
	size_t mat_size = std::any_cast<std::vector<std::vector<double>>>(gar.get_parameter("cost_matrix", {})).size();

	double best_fit = -INFINITY; std::string best_obj_str = "";
	for(auto i = pop.begin(); i != pop.end(); ++i){
		std::stringstream obj, fit;
		obj << bool_string_to_perm(*i, mat_size);
		double fit_val = gar.fitness_func(gar, *i);
		fit << fit_val;
		self->newPopulation.addRow(obj.str(), fit.str());

		if(fit_val > best_fit)
		{ best_fit = fit_val; best_obj_str = obj.str(); }
	}

	std::stringstream fit; fit << best_fit;
	self->bestObj.addRow(best_obj_str, fit.str());
}

StepFrame::StepFrame():
	mainStepBox(Gtk::ORIENTATION_VERTICAL, 10),
	nextStep("Следующий шаг"),
	initPopulation("Особи", "Приспособленность"),
	crossingOver("Родители", "Потомки"),
	mutations("До мутации", "После мутации"),
	newPopulation("Новая популяция", ""),
	bestObj("Лучшая особь", "")
{
	set_label("Пошаговая визуализация:");
	mainStepBox.set_border_width(20);

	tables = {&initPopulation, &crossingOver,
			&mutations, &newPopulation, &bestObj};

	for (auto pTable: tables){
		mainStepBox.pack_start(*pTable);
	}

	nextStep.signal_clicked().connect( sigc::mem_fun(*this,
		&StepFrame::newStep) );
	nextStep.set_halign(Gtk::ALIGN_END);
	nextStep.set_valign(Gtk::ALIGN_END);
	mainStepBox.pack_start(nextStep);

	add(mainStepBox);
}
void StepFrame::initGARunner(SettingsFrame& sfr, std::vector<std::vector<double>> matrix)
{
	// TODO: change mutation chance
	gar = new GARunner<BoolString>(sfr.getPopSize(), generate_rand_perms(sfr.getN(), sfr.getPopSize()), 1.0, perm_fitness_func,
											multi_point_crossingover, density_mutation_op, roulette_bs_selection_op, elite_truncation_survivor_selection_op);
	gar->add_parameter("step_frame", this);
	gar->add_parameter("cost_matrix", matrix);
	gar->callback_iteration_start = GACBIterationStart;
	gar->callback_new_children = GACBNewChildren;
	gar->callback_mutation = GACBMutation;
	gar->callback_new_population = GACBNewPopulation;

	newStep();
}

void StepFrame::newStep()
{
	gar->do_iteration();
	//gar->thread_iterate_count(1);
}
