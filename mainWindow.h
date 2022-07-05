#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "SettingsFrame.h"
#include "InputFrame.h"
#include "StepFrame.h"
#include "ResultFrame.h"
#include "ChooseFileWindow.h"

class MainWindow : public Gtk::Window
{
private:
	Gtk::Box mainBox;
	Gtk::Button nextStep;
	SettingsFrame settings;
	InputFrame input;
	StepFrame steps;
	ResultFrame result;

	void changeFrame();	
	unsigned short mode = 0;
public:
	MainWindow();
	virtual ~MainWindow();

};

#endif
