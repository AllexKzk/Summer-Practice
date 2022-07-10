#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <gtkmm.h>
#include <string>

//КЛАСС ОКНА ОШИБКИ
//достаточно в необходимом месте запустить конструктор класса
//и на экран будет выведено сообщение об ошибке

class ErrorWindow: public Gtk::Window
{
private:
	Gtk::MessageDialog dialog;

public:
	ErrorWindow(std::string errorName, std::string error);

};

#endif
