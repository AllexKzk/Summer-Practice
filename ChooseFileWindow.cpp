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

	//Show the dialog and wait for a user response:
}

unsigned short ChooseFileWindow::open()
{
	int result = dialog.run();

	switch(result)
	{
		case (Gtk::RESPONSE_OK):
		  std::cout << "Select clicked." << std::endl;
		  std::cout << "Folder selected: " << dialog.get_filename()
		      << std::endl;
		  return 1;
		case (Gtk::RESPONSE_CANCEL):
		  std::cout << "Cancel clicked." << std::endl;
		  return 0;
		default:
		  std::cout << "Unexpected button clicked." << std::endl;
		  return 0;
	}

	return 0;
}

ChooseFileWindow::~ChooseFileWindow(){}