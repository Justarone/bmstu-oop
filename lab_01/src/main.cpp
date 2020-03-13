#include "../include/main.h"


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv);

    event_t load_event = init_event(LOAD_DATA, NO_CODE);
    event_data_t load_data = init_data(POINTS_FILE);
    event_data_t error_data = init_data();

    err_t rc = task_manager(load_event, load_data);
    if (rc)
    {
        event_t quit_event = init_event(QUIT, NO_CODE);
        task_manager(quit_event, error_data);
        return rc;
    }

    myApplication application(FILENAME);  
    return app->run(*application.get_window());
}

