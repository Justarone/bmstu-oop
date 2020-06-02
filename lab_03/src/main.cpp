#include "main_window.hpp"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv);

    mainWindow application("meta/interface.glade");  
    return app->run(*application.get_window());
}

