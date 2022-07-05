#ifndef STEPFRAME_H
#define STEPFRAME_H

#include <gtkmm.h>
#include <vector>
#include "StepTable.h"

class StepFrame: public Gtk::Frame
{
private:
	Gtk::Box mainStepBox;

	StepTable initPopulation, chosenParents, crossingOver, 
		mutations, newPopulation, bestObj;
	std::vector<StepTable*> tables;
	
	Gtk::Button nextStep;
	std::string fileName = "exp.txt";

public:
	StepFrame();
	virtual ~StepFrame();

	void unparseFile();
	void newStep();

};

#endif