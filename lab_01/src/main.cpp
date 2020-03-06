#include <gtkmm.h>
#include <iostream>

#include "../include/constants.h"
#include "../include/application.h"
#include "../include/iomodule.h"


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv);
    myApplication application(FILENAME);  
    return app->run(*application.get_window());
}

