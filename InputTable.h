#ifndef INPUTTABLE_H
#define INPUTTABLE_H

#include <gtkmm.h>
#include <string>
#include <vector>

class InputTable: public Gtk::ScrolledWindow
{
private:
	Gtk::Grid grid;
	size_t mat_size;
public:
	InputTable(unsigned int size);
	virtual ~InputTable();

	void resizeTable(unsigned int size);
	std::vector<std::vector<double>> getMatrix();
};

#endif
