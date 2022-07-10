#include "ErrorWindow.h"

ErrorWindow::ErrorWindow(std::string errorName, std::string errorComment):
	dialog (*this, "Error: " + errorName, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK)
{
	dialog.set_secondary_text(errorComment);

	dialog.run();
}