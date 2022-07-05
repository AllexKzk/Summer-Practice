#include "StepFrame.h"

#include <iostream>

StepFrame::StepFrame():
	mainStepBox(Gtk::ORIENTATION_VERTICAL, 10),
	nextStep("Следующий шаг"),
	initPopulation("Особи", "Приспособленность"),
	chosenParents("Особи", "Вероятность"),
	crossingOver("Родители", "Потомки"),
	mutations("До мутации", "После мутации"),
	newPopulation("Новая популяция", ""),
	bestObj("Лучшая особь", "")
{
	set_label("Пошаговая визуализация:");
	mainStepBox.set_border_width(20);

	tables = {&initPopulation, &chosenParents, &crossingOver,
			&mutations, &newPopulation, &bestObj};

	for (auto pTable: tables){
		pTable->importFromFile(fileName);
		mainStepBox.pack_start(*pTable);
	}

	nextStep.signal_clicked().connect( sigc::mem_fun(*this, 
		&StepFrame::newStep) );
	nextStep.set_halign(Gtk::ALIGN_END);
	nextStep.set_valign(Gtk::ALIGN_END);
	mainStepBox.pack_start(nextStep);

	add(mainStepBox);
}

StepFrame::~StepFrame(){}

void StepFrame::newStep()
{	
	for (auto pTable: tables)
		pTable->importFromFile(fileName);
}

void StepFrame::unparseFile()
{

}