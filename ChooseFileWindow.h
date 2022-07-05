#ifndef CHOOSEFILEWINDOW_H
#define CHOOSEFILEWINDOW_H

#include <gtkmm.h>
#include <iostream>

class ChooseFileWindow: public Gtk::Window
{
private:
	Gtk::FileChooserDialog dialog;
public:
	ChooseFileWindow();
	unsigned short open();
	virtual ~ChooseFileWindow();
};

#endif