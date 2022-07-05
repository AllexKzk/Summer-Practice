#include "StepTable.h"

StepTable::StepTable(Glib::ustring firstColumnName, Glib::ustring secondColumnName)
{
	add(treeView);
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

	refColumns = Gtk::ListStore::create(columns);
	treeView.set_model(refColumns);

	treeView.append_column(firstColumnName, columns.column1);
	treeView.append_column(secondColumnName, columns.column2);

}

StepTable::~StepTable(){}

void StepTable::importFromFile(std::string fileName)
{
	std::string str1, str2;
	std::fstream file;
	file.open(fileName, std::fstream::in); 

	Gtk::TreeModel::Row row;
	refColumns->clear();
	while (file >> str1 >> str2){
		row = *(refColumns->append());
		row[columns.column1] = str1;
		row[columns.column2] = str2;

		std::cout << str1 << " " << str2 << std::endl;
	}
	file.close();

}