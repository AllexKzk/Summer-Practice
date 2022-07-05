#ifndef SPINBOX_H
#define SPINBOX_H

#include <gtkmm.h>

class SpinBox: public Gtk::Box 
{
private:
	Gtk::Label label;
public:
	Gtk::SpinButton spin;
	SpinBox(Glib::ustring name, Glib::RefPtr<Gtk::Adjustment> adjustment);
	virtual ~SpinBox();
};

#endif