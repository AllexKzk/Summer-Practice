#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "SettingsFrame.h"
#include "InputFrame.h"
#include "StepFrame.h"
#include "ResultFrame.h"
#include "ChooseFileWindow.h"
#include "ErrorWindow.h"

class MainWindow : public Gtk::Window
{
private:
	Gtk::Box mainBox;
	Gtk::Button nextStep;

	Gtk::ProgressBar activityBar;
	sigc::connection timeoutConnection;
	bool timeCheck();
	
	SettingsFrame settings;
	InputFrame input;
	StepFrame steps;
	ResultFrame result;

	std::string dataFileName = "data";

	void changeFrame();
	unsigned short mode = 0;
public:
	MainWindow();
	virtual ~MainWindow();

};

#endif
