#include "ResultFrame.h"

ResultFrame::ResultFrame():
	mainResBox(Gtk::ORIENTATION_VERTICAL, 10),
	answer("Работник", "Работа")
{
	set_label("Результат:");
	mainResBox.set_border_width(20);
	answer.set_propagate_natural_height();
	mainResBox.pack_start(answer);

	add(mainResBox);
}

ResultFrame::~ResultFrame(){}

void ResultFrame::setResult(Permutation perm)
{
	answer.clear();
	for(size_t i = 0; i < perm.size(); ++i){
		std::stringstream is; is << i;
		std::stringstream ws; ws << perm[i];
		answer.addRow(is.str(), ws.str());
	}
}
