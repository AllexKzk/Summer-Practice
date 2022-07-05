#include "SettingsFrame.h"

SettingsFrame::SettingsFrame():
	settingsMainBox(Gtk::ORIENTATION_VERTICAL, 10),
	genAlgSetBox(Gtk::ORIENTATION_VERTICAL, 10),
	
	inFile("Через файл"), inProgram("Через программу"),

	unknownVarSpin("Значение N: ", Gtk::Adjustment::create(1.0, 1.0, 100, 1.0, 5.0, 0.0)),
	popBox("Начальный размер популяции: ", Gtk::Adjustment::create(1.0, 1.0, 1, 1.0, 5.0, 0.0)),
	ruleBox("Критерий остановки: ", Gtk::Adjustment::create(1.0, 1.0, 1, 1.0, 5.0, 0.0)),
	infBox("Коэффициент влияния: ", Gtk::Adjustment::create(1.0, 1.0, 1, 1.0, 5.0, 0.0)),
	mutBox("Плотность мутации: ", Gtk::Adjustment::create(1.0, 1.0, 1, 1.0, 5.0, 0.0)),
	selBox("Количество особей элитного отбора: ", Gtk::Adjustment::create(1.0, 1.0, 1, 1.0, 5.0, 0.0))

{

	set_label("Настройки");

	inputSetFrame.set_label("Ввод значений");
	genAlgSetFrame.set_label("Настройки генетического алгоритма");

	settingsMainBox.set_border_width(30);
	inputSetBox.set_border_width(10);
	genAlgSetBox.set_border_width(10);

	inFile.join_group(inProgram);

	unknownVarSpin.spin.signal_value_changed().connect(sigc::mem_fun(*this,
              &SettingsFrame::rangeCorrection));

	inputSetBox.pack_start(inFile);
	inputSetBox.pack_start(inProgram);
	inputSetFrame.add(inputSetBox);
	settingsMainBox.pack_start(inputSetFrame);

	genAlgSetBox.pack_start(unknownVarSpin);
	spinBoxVec = {&popBox, &ruleBox, &infBox, &mutBox, &selBox};
	for (auto pBox: spinBoxVec)
		genAlgSetBox.pack_start(*pBox);

	genAlgSetFrame.add(genAlgSetBox);
	settingsMainBox.pack_start(genAlgSetFrame);

	add(settingsMainBox);

	show_all_children();
}

SettingsFrame::~SettingsFrame(){}

void SettingsFrame::rangeCorrection()
{
	for (auto pBox: spinBoxVec)
	{
		unsigned int upperValue = unknownVarSpin.spin.get_value();
		unsigned int oldValue = pBox->spin.get_value();
		unsigned int curValue = std::min(upperValue, oldValue);
		pBox->spin.set_adjustment(Gtk::Adjustment::create(curValue, 1.0, 
									upperValue, 1.0, 5.0, 0.0));
	}
}

bool SettingsFrame::isProgramInput(){
	return inProgram.get_active();
}

unsigned int SettingsFrame::getVar(){
	return unknownVarSpin.spin.get_value();
}