#include "StepFrame.h"

#include <iostream>
#include <glibmm.h>

#include "algorithm/perm_ga.h"
#include "algorithm/perm_conv.h"
#include "ga_runner/recombination_ops.h"
#include "ga_runner/mutation_ops.h"
#include "ga_runner/parent_selection_ops.h"
#include "ga_runner/survivor_selection_ops.h"

static void GACBIterationStart(GARunner<BoolString>& gar, std::vector<BoolString> pop)
{
	StepFrame* self = std::any_cast<StepFrame*>(gar.get_parameter("step_frame", nullptr));
	--self->iteration_left;
	self->queueClearTable(StepFrameTable_initPopulation);
	self->queueClearTable(StepFrameTable_crossingOver);
	self->queueClearTable(StepFrameTable_mutations);
	self->queueClearTable(StepFrameTable_newPopulation);
	self->queueClearTable(StepFrameTable_bestObj);

	size_t mat_size = std::any_cast<std::vector<std::vector<double>>>(gar.get_parameter("cost_matrix", {})).size();
	for(auto i = pop.begin(); i != pop.end(); ++i){
		std::stringstream obj, fit;
		obj << bool_string_to_perm(*i, mat_size);
		fit << gar.fitness_func(gar, *i);
		self->queueTableRow(StepFrameTable_initPopulation, obj.str(), fit.str());
	}

	*self->log_out << "---- iterations left: " << self->iteration_left + 1 << " ----\n";
}
static void GACBNewChildren(GARunner<BoolString>& gar, std::pair<BoolString, BoolString> parents, std::vector<BoolString> children)
{
	StepFrame* self = std::any_cast<StepFrame*>(gar.get_parameter("step_frame", nullptr));
	size_t mat_size = std::any_cast<std::vector<std::vector<double>>>(gar.get_parameter("cost_matrix", {})).size();

	std::stringstream parents_str, children_str;
	parents_str << bool_string_to_perm(parents.first, mat_size) << " " << bool_string_to_perm(parents.second, mat_size);
	for(auto i = children.begin(); i != children.end(); ++i)
		children_str << bool_string_to_perm(*i, mat_size) << ' ';
	self->queueTableRow(StepFrameTable_crossingOver, parents_str.str(), children_str.str());
	*self->log_out << "parents: " << parents_str.str() << "\tchildren: " << children_str.str() << "\n";
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
		self->queueTableRow(StepFrameTable_mutations, before_mut.str(), after_mut.str());
		if(before_mut.str() != after_mut.str())
			*self->log_out << "mutation: " << before_mut.str() << "--> " << after_mut.str() << '\n';
	}
}
static void GACBNewPopulation(GARunner<BoolString>& gar, std::vector<BoolString> pop)
{
	StepFrame* self = std::any_cast<StepFrame*>(gar.get_parameter("step_frame", nullptr));
	size_t mat_size = std::any_cast<std::vector<std::vector<double>>>(gar.get_parameter("cost_matrix", {})).size();

	*self->log_out << "new population:\n";
	double best_fit = -INFINITY; std::string best_obj_str = "";
	for(auto i = pop.begin(); i != pop.end(); ++i){
		std::stringstream obj, fit;
		obj << bool_string_to_perm(*i, mat_size);
		double fit_val = gar.fitness_func(gar, *i);
		fit << fit_val;
		self->queueTableRow(StepFrameTable_newPopulation, obj.str(), fit.str());
		*self->log_out << obj.str() << '\t' << fit.str() << '\n';

		if(fit_val > best_fit)
		{ best_fit = fit_val; best_obj_str = obj.str(); }
	}
	*self->log_out << "best individual: " << best_obj_str << '(' << best_fit << ")\n";

	std::stringstream fit; fit << best_fit;
	self->queueTableRow(StepFrameTable_bestObj, best_obj_str, fit.str());
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
	set_valign(Gtk::ALIGN_FILL);
	mainStepBox.set_valign(Gtk::ALIGN_FILL);
	mainStepBox.set_border_width(20);

	tables = {&initPopulation, &crossingOver,
			&mutations, &newPopulation, &bestObj};

	for (auto pTable: tables){
		mainStepBox.pack_start(*pTable);
		pTable->set_propagate_natural_height();
	}

	nextStep.signal_clicked().connect( sigc::mem_fun(*this,
		&StepFrame::newStep) );
	nextStep.set_halign(Gtk::ALIGN_END);
	nextStep.set_valign(Gtk::ALIGN_END);
	mainStepBox.pack_start(nextStep);

	add(mainStepBox);

	pthread_mutex_init(&table_queue_mutex, NULL);
	sigc::slot<bool()> timer_slot = sigc::mem_fun(*this, &StepFrame::processQueue);
	auto conn = Glib::signal_timeout().connect(timer_slot, 10);
}
StepFrame::~StepFrame()
{
	if(log_out){
		log_out->close();
		delete log_out;
	}
}
void StepFrame::initGARunner(SettingsFrame& sfr, std::vector<std::vector<double>> matrix)
{
	iteration_left = sfr.getIterationStop();
	gar = new GARunner<BoolString>(sfr.getPopSize(), generate_rand_perms(sfr.getN(), sfr.getPopSize()), 1.0, perm_fitness_func,
											multi_point_crossingover, density_mutation_op, roulette_bs_selection_op, elite_truncation_survivor_selection_op);
	gar->add_parameter("step_frame", this);
	gar->add_parameter("cost_matrix", matrix);
	gar->callback_iteration_start = GACBIterationStart;
	gar->callback_new_children = GACBNewChildren;
	gar->callback_mutation = GACBMutation;
	gar->callback_new_population = GACBNewPopulation;

	if(log_out){
		log_out->close();
		delete log_out;
	}
	log_out = new std::ofstream(log_out_fname);

	newStep();
}

void StepFrame::newStep()
{
	gar->thread_iterate_count(1);
}


void StepFrame::queueTableRow(StepFrameTableEnum tb, std::string s1, std::string s2)
{
	pthread_mutex_lock(&table_queue_mutex);
	table_queue[tb].push_back({s1, s2});
	pthread_mutex_unlock(&table_queue_mutex);
}
void StepFrame::queueClearTable(StepFrameTableEnum tb)
{
	pthread_mutex_lock(&table_queue_mutex);
	table_queue[tb].clear();
	pthread_mutex_unlock(&table_queue_mutex);
}
bool StepFrame::processQueue()
{
	pthread_mutex_lock(&table_queue_mutex);
	for(size_t i = 0; i < StepFrameTableCount; ++i){
		tables[i]->clear();
		for(size_t j = 0; j < table_queue[i].size(); ++i)
			 tables[i]->addRow(table_queue[i][j].first, table_queue[i][j].second);
	}
	pthread_mutex_unlock(&table_queue_mutex);
	return true;
}

bool StepFrame::isDone() { return iteration_left <= 0; }
void StepFrame::workUntilDone() { gar->thread_iterate_count(iteration_left); }
Permutation StepFrame::getResult()
{
	std::vector<BoolString>& vbs = gar->get_current_population();
	BoolString min; double min_fit = -INFINITY;
	for(auto i = vbs.begin(); i != vbs.end(); ++i)
		if(gar->fitness_func(*gar, *i) > min_fit)
		{ min_fit = gar->fitness_func(*gar, min); min = *i; }

    size_t mat_size = std::any_cast<std::vector<std::vector<double>>>(gar->get_parameter("cost_matrix", {})).size();
	return bool_string_to_perm(min, mat_size);
}
