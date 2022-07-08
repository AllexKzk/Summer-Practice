#ifndef STEPFRAME_H
#define STEPFRAME_H

#include <gtkmm.h>
#include <vector>
#include "StepTable.h"
#include "InputFrame.h"
#include "SettingsFrame.h"

#include "ga_runner/ga_runner.h"

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

public:
	StepFrame();
	void initGARunner(SettingsFrame& sfr, std::vector<std::vector<double>> matrix);

	void newStep();

	std::vector<BoolString> children_before_mut;
};

#endif
