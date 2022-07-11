#include "InputFrame.h"
#include "ErrorWindow.h"
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
	input->set_propagate_natural_height();
	isGui = true;
	add(*input);
	input->show();
}

bool InputFrame::addTable(std::string filePath, unsigned N)
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
				if(file.eof()){
					ErrorWindow("Неожиданный конец файла", "Ошибка чтения матрицы затрат с файла: неожиданный конец файла (недостаточно данных для заданного размера матрицы)");
					return false;
				}
				else if(file.fail()){
					ErrorWindow("Не удалось считать файл", "Ошибка чтения матрицы затрат с файла: не удалось считать файл (проверьте права доступа к файлу)");
					return false;
				}
				file >> num;	
				std::cout << num << " ";		
				if (num <= 0){
					ErrorWindow("Ошибка значений в матрице", "Значения затрат в матрице должны быть > 0");
					return false;
				}
				buf.push_back(num);
			}
			std::cout << std::endl;
			matrix.push_back(buf);
		}
		file.close();
		return true;
	}
	ErrorWindow("Не удалось открыть файл", "Повторите попытку или выберите другой файл.");
	return false;
}

std::vector<std::vector<double>> InputFrame::getMatrix()
{
	if (isGui)			//GUI
		return ((InputTable*) get_child())->getMatrix();
	return matrix;		//FILE
}
