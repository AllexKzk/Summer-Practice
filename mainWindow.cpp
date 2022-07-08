#include "mainWindow.h"

MainWindow::MainWindow():
	mainBox(Gtk::ORIENTATION_VERTICAL, 10),
	nextStep("Следующий шаг")
{
	set_title("Генетический алгоритм");

	mainBox.set_border_width(10);

	nextStep.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::changeFrame));
	nextStep.set_halign(Gtk::ALIGN_END);
	nextStep.set_valign(Gtk::ALIGN_END);

	mainBox.pack_start(settings);
	mainBox.pack_start(input);
	mainBox.pack_start(steps);
	mainBox.pack_start(result);
	mainBox.pack_start(nextStep);
	add(mainBox);

	show_all_children();
	input.hide();
	steps.hide();
	result.hide();
}

MainWindow::~MainWindow(){}

void MainWindow::changeFrame(){
	switch(mode)
	{
		case 0:
			if (settings.isProgramInput()){
				input.addTable(settings.getN());
				settings.hide();
				input.show();
				mode = 1;
			}
			else {
				ChooseFileWindow fileWindow;
				mode = fileWindow.open();
				if (mode){
					settings.hide();
					input.addTable(fileWindow.getFilePath(), settings.getN());
					changeFrame();
				}
			}
			break;
		case 1:
			input.hide();
			steps.initGARunner(settings, input.getMatrix());
			steps.show();
			nextStep.set_label("К результату");
			mode = 2;
			break;
		case 2:
			steps.hide();
			result.show();

			nextStep.set_label("Задать новые данные");
			mode = 3;
			break;
		case 3:
			result.hide();
			settings.show();
			nextStep.set_label("Следующий шаг");
			mode = 0;
			break;
	}
}
