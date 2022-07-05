#include "SpinBox.h"

SpinBox::SpinBox(Glib::ustring name, Glib::RefPtr<Gtk::Adjustment> adjustment):
	label(name),
	spin(adjustment)
{	
	set_border_width(10);
	
	spin.set_wrap();
	spin.set_halign(Gtk::ALIGN_END);
	
	label.set_halign(Gtk::ALIGN_START);

	pack_start(label);
	pack_start(spin);
}	

SpinBox::~SpinBox(){}