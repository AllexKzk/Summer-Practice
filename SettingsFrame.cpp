#include "SettingsFrame.h"
#include <climits>

SettingsFrame::SettingsFrame():
	settingsMainBox(Gtk::ORIENTATION_VERTICAL, 10),
	genAlgSetBox(Gtk::ORIENTATION_VERTICAL, 10),
	inFile("Через файл"), inProgram("Через программу"),

	unknownVarSpin("Значение N: ", Gtk::Adjustment::create(4, 1, 100, 1, 5, 0)),
	popBox("Начальный размер популяции: ", Gtk::Adjustment::create(30, 1, 1000, 5, 20, 0)),
	ruleBox("Остановка после итераций: ", Gtk::Adjustment::create(1000, 1, UINT_MAX, 100, 1000, 0)),
	infBox("Влияение приспособленности на выбор родителя (%): ", Gtk::Adjustment::create(80, 0, 100, 10, 25, 0), 1.0, 2.0),
	mutBox("Плотность мутации (% от всех генов): ", Gtk::Adjustment::create(1, 0, 100, 1, 5, 0), 1.0, 2.0),
	selBox("Количество особей элитного отбора (%): ", Gtk::Adjustment::create(20, 0, 100, 5, 10, 0), 1.0, 2.0)

{

	set_label("Настройки");

	inputSetFrame.set_label("Ввод значений");
	genAlgSetFrame.set_label("Настройки генетического алгоритма");

	settingsMainBox.set_border_width(30);
	inputSetBox.set_border_width(10);
	genAlgSetBox.set_border_width(10);

	inFile.join_group(inProgram);

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

bool SettingsFrame::isProgramInput()
{
	return inProgram.get_active();
}

unsigned SettingsFrame::getN() { return unknownVarSpin.spin.get_value(); }
unsigned SettingsFrame::getPopSize() { return popBox.spin.get_value(); }
unsigned SettingsFrame::getIterationStop() { return ruleBox.spin.get_value(); }
double SettingsFrame::getFitnessRouletteInfluence() { return infBox.spin.get_value() / 100.; }
double SettingsFrame::getMutationDensity() { return mutBox.spin.get_value() / 100.; }
double SettingsFrame::getEliteFraction() { return selBox.spin.get_value() / 100.; }
