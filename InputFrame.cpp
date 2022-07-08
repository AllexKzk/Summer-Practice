#include "InputFrame.h"
#include <string>

InputFrame::InputFrame():
	inputMainBox(Gtk::ORIENTATION_VERTICAL, 10),
	input(0)
{
	set_label("Введите значения: ");
	inputMainBox.set_border_width(10);
	inputMainBox.pack_start(input);

	add(inputMainBox);

	show_all_children();
}

InputFrame::~InputFrame(){}


void InputFrame::addTable(unsigned int size)
{
	input.resizeTable(size);
}

InputTable& InputFrame::getInputTable()
{
	return input;
}
