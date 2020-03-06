#include <gtkmm.h>
#include <iostream>
#include "../include/constants.h"
#include "../include/application.h"
#include "../include/data_processing.h"


int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    if (read_from_file(POINTS_FILE))
        return READ_ERROR;
    auto app = Gtk::Application::create(argc, argv);
    myApplication application(FILENAME);  
    return app->run(*application.get_window());
}

