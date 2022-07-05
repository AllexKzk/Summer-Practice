#ifndef INPUTFRAME_H
#define INPUTFRAME_H

#include <gtkmm.h>
#include "InputTable.h"

class InputFrame: public Gtk::Frame
{
private:
	Gtk::Box inputMainBox;
	InputTable input;
public:
	InputFrame();
	virtual ~InputFrame();
	void addTable(unsigned int size);
};

#endif