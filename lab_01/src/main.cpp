#include "../include/main.h"


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv);

    event_t load_event = { LOAD_DATA, NO_CODE, { NULL, NULL } };

    err_t rc = task_manager(load_event);
    if (rc)
    {
        event_t quit_event = { QUIT, NO_CODE, { NULL, NULL } };
        task_manager(quit_event);
    }

    myApplication application(FILENAME);  
    return app->run(*application.get_window());
}

