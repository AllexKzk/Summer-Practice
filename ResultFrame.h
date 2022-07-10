#ifndef RESULTFRAME_H
#define RESULTFRAME_H

#include <gtkmm.h>
#include "StepTable.h"
#include "algorithm/perm_ga.h"

class ResultFrame: public Gtk::Frame
{
private:
	StepTable answer;
	Gtk::Box mainResBox;

public:
	ResultFrame();
	virtual ~ResultFrame();

	void setResult(Permutation perm);
};

#endif
