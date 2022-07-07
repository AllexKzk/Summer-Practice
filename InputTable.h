#ifndef INPUTTABLE_H
#define INPUTTABLE_H

#include <gtkmm.h>
#include <string>
#include <fstream>

class InputTable: public Gtk::ScrolledWindow
{
private:
	Gtk::Grid grid;
public:
	InputTable(unsigned int size);
	virtual ~InputTable();	

	void resizeTable(unsigned int size);
	void saveData(unsigned int size, std::string fileName);
};

#endif