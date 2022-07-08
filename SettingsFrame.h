#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include <gtkmm.h>
#include <fstream>
#include <string>
#include <vector>
#include "SpinBox.h"

class SettingsFrame: public Gtk::Frame
{
private:
	Gtk::Box settingsMainBox, inputSetBox, genAlgSetBox;

	SpinBox popBox, ruleBox, infBox, mutBox, selBox, unknownVarSpin;
	std::vector<SpinBox*> spinBoxVec;

	Gtk::Frame inputSetFrame, genAlgSetFrame;

	Gtk::RadioButton inFile, inProgram;

public:
	SettingsFrame();
	virtual ~SettingsFrame();
	bool isProgramInput();

	unsigned getN();
	unsigned getPopSize();
	unsigned getIterationStop();
	double getFitnessRouletteInfluence();
	double getMutationDensity();
	double getEliteFraction();
};

#endif
