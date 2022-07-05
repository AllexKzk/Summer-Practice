#include "InputTable.h"

InputTable::InputTable(unsigned int size)
{

	set_border_width(10);
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);

	grid.set_row_spacing(5);
	grid.set_column_spacing(5);

	resizeTable(size);

	add(grid);

	show_all_children();
}

InputTable::~InputTable(){}

void InputTable::resizeTable(unsigned int size)
{
	for(int i = 0; i < size + 1; i++)
	{
		for(int j = 0; j < size + 1; j++)
		{
			if (i == 0 && j != 0 ){
				auto label = Gtk::make_managed<Gtk::Label>(std::to_string(j));
				grid.attach(*label, i, j);
			}
			else if (i != 0 && j == 0 ){
				auto label = Gtk::make_managed<Gtk::Label>(std::to_string(i));
				grid.attach(*label, i, j);
			}
			else if (i != 0 && j != 0 ){
				auto spin = Gtk::make_managed<Gtk::SpinButton>(Gtk::Adjustment::create(1.0, 1.0, 20, 1.0, 5.0, 0.0));
				grid.attach(*spin, i, j);
			}
		}
	}
	show_all_children();
}

