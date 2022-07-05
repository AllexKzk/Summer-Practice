#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include <gtkmm.h>
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
	
	void rangeCorrection();

public:
	SettingsFrame();
	virtual ~SettingsFrame();
	bool isProgramInput();
	unsigned int getVar();
};

#endif