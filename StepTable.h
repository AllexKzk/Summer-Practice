#ifndef STEPTABLE_H
#define STEPTABLE_H

#include <gtkmm.h>
#include <fstream>
#include <iostream>
#include <string>

class StepTable: public Gtk::ScrolledWindow
{
protected:
	class ModelColumns: public Gtk::TreeModel::ColumnRecord
	{
	public:
		Gtk::TreeModelColumn<Glib::ustring> column1;
		Gtk::TreeModelColumn<Glib::ustring> column2;

		ModelColumns() { add(column1); add(column2); }
	};

	ModelColumns columns;
	Gtk::TreeView treeView;
	Glib::RefPtr<Gtk::ListStore> refColumns;

public:
	StepTable(Glib::ustring firstColumnName, Glib::ustring secondColumnName);
	virtual ~StepTable();

	void addRow(std::string e1, std::string e2);
	void clear();

	void importFromFile(std::string fileName);
};

#endif
