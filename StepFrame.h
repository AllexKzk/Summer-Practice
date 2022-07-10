#ifndef STEPFRAME_H
#define STEPFRAME_H

#include <gtkmm.h>
#include <vector>
#include <pthread.h>
#include "StepTable.h"
#include "InputFrame.h"
#include "SettingsFrame.h"

#include "algorithm/perm_conv.h"
#include "ga_runner/ga_runner.h"

enum StepFrameTableEnum{
	StepFrameTable_initPopulation,
	StepFrameTable_crossingOver,
	StepFrameTable_mutations,
	StepFrameTable_newPopulation,
	StepFrameTable_bestObj,

	StepFrameTableCount
};

class StepFrame: public Gtk::Frame
{
private:
	Gtk::Box mainStepBox;
public:
	StepTable initPopulation, crossingOver,
		mutations, newPopulation, bestObj;
private:
	std::vector<StepTable*> tables;
	Gtk::Button nextStep;

	GARunner<BoolString>* gar = nullptr;

	// Очередь на добавление элементов в таблицы/очистку таблиц (при добавлении через callback в отдельном потоке возникает race condition)
	pthread_mutex_t table_queue_mutex;
	std::vector<std::pair<std::string, std::string>> table_queue[StepFrameTableCount];

public:
	StepFrame();
	void initGARunner(SettingsFrame& sfr, std::vector<std::vector<double>> matrix);

	void newStep();

	std::vector<BoolString> children_before_mut;

	void queueTableRow(StepFrameTableEnum tb, std::string s1, std::string s2);
	void queueClearTable(StepFrameTableEnum tb);
	bool processQueue();

	// Готовность конечного результата
	long long iteration_left = 0;
	bool isDone();
	void workUntilDone();

	Permutation getResult();
};

#endif
