#include "InputFrame.h"
#include <iostream>
InputFrame::InputFrame()
{
	set_label("Введите значения: ");
	show_all_children();
}

InputFrame::~InputFrame(){}


void InputFrame::addTable(unsigned int size)
{
	if (get_child())
		remove();
	auto input = Gtk::make_managed<InputTable>(size);
	isGui = true;
	add(*input);
	input->show();
}

void InputFrame::addTable(std::string filePath, unsigned N)
{
	std::fstream file;
	file.open(filePath, std::fstream::in);
	if (file.is_open())
	{
		isGui = false;
		if (matrix.size())
			matrix.clear();
		for (unsigned i = 0; i < N; ++i)
		{
			std::vector<double> buf;
			double num;
			for (unsigned j = 0; j < N; ++j)
			{
				file >> num;				//try/catch read
				std::cout << num << " ";
				buf.push_back(num);
			}
			std::cout << std::endl;
			matrix.push_back(buf);
		}
		file.close();
	}
}

std::vector<std::vector<double>> InputFrame::getMatrix()
{
	if (isGui)			//GUI
		return ((InputTable*) get_child())->getMatrix();
	return matrix;		//FILE
}
