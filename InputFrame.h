#ifndef INPUTFRAME_H
#define INPUTFRAME_H

#include "InputTable.h"
#include <gtkmm.h>
#include <fstream>

class InputFrame: public Gtk::Frame
{
private:
	std::vector<std::vector<double>> matrix;
	bool isGui = false;
public:
	InputFrame();
	virtual ~InputFrame();
	void addTable(unsigned int size);				//GUI
	void addTable(std::string filePath, unsigned N);//FILE
	std::vector<std::vector<double>> getMatrix();
};

#endif
