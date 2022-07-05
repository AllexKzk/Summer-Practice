#include "ResultFrame.h"

ResultFrame::ResultFrame():
	mainResBox(Gtk::ORIENTATION_VERTICAL, 10),
	answer("Работник", "Работа")
{
	set_label("Результат:");
	mainResBox.set_border_width(20);

	answer.importFromFile(fileName);
	mainResBox.pack_start(answer);

	add(mainResBox);
}

ResultFrame::~ResultFrame(){}