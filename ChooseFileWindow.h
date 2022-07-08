#ifndef CHOOSEFILEWINDOW_H
#define CHOOSEFILEWINDOW_H

#include <gtkmm.h>
#include <string>

class ChooseFileWindow: public Gtk::Window
{
private:
	Gtk::FileChooserDialog dialog;
	std::string filePath;
public:
	ChooseFileWindow();
	unsigned short open();
	std::string getFilePath();
	virtual ~ChooseFileWindow();
};

#endif