#ifndef RESULTFRAME_H
#define RESULTFRAME_H

#include <gtkmm.h>
#include "StepTable.h"

class ResultFrame: public Gtk::Frame
{
private:
	StepTable answer;
	Gtk::Box mainResBox;
	std::string fileName = "res.txt";

public:
	ResultFrame();
	virtual ~ResultFrame();
};

#endif