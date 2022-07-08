#include "InputFrame.h"
#include <string>

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
	add(*input);
	input->show();
}

InputTable& InputFrame::getInputTable()
{
	InputTable* table = (InputTable*) get_child();
	return *table;
}
