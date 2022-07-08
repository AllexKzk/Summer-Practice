#include "ChooseFileWindow.h"

ChooseFileWindow::ChooseFileWindow():
	dialog("Выберите файл", Gtk::FILE_CHOOSER_ACTION_OPEN)
{
	dialog.set_transient_for(*this);

	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);

	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog.add_filter(filter_text);
}

unsigned short ChooseFileWindow::open()
{
	int result = dialog.run();

	switch(result)
	{
		case (Gtk::RESPONSE_OK):
		  filePath = dialog.get_filename();
		  return 1;
		case (Gtk::RESPONSE_CANCEL):
		  return 0;
		default:
		  return 0;
	}

	return 0;
}

std::string ChooseFileWindow::getFilePath(){ return filePath; }

ChooseFileWindow::~ChooseFileWindow(){}