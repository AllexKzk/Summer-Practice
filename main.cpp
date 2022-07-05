#include "mainWindow.h"
#include <iostream>

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "sum.project");

  MainWindow window;

  //Shows the window and returns when it is closed.
  return app->run(window);
}