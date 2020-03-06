#include "../include/application.h"
#include "../include/app_codes.h"

static const char *MOVE_NAMES[] = { "move_up", "move_down", "move_right",
    "move_left", "move_front", "move_back" };
static const char *SCALE_NAMES[] = { "scale_plus", "scale_minus" };
static const char *ROTATE_NAMES[] = { "rotate_up", "rotate_down", "rotate_left", 
    "rotate_right", "rotate_rightup", "rotate_leftup" };

myApplication::myApplication(const char* const filename)
{
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    builder->add_from_file(filename);

    builder->get_widget("main_window", main_window);
    main_window->set_title("Лабораторная №1.");

    builder->get_widget("drawing_area", drawing_area);

    
    for (int i = 0; i < MOVE_SIZE; i++)
    {
        builder->get_widget(MOVE_NAMES[i], move_btns[i]);
        move_btns[i]->signal_clicked().connect(sigc::bind<char, char>(sigc::mem_fun(*this,
                        &myApplication::on_button_clicked), MOVE, i));
    }

    for (int i = 0; i < SCALE_SIZE; i++)
    {
        builder->get_widget(SCALE_NAMES[i], scale_btns[i]);
        scale_btns[i]->signal_clicked().connect(sigc::bind<char, char>(sigc::mem_fun(*this,
                        &myApplication::on_button_clicked), SCALE, i));
    }

    for (int i = 0; i < ROTATE_SIZE; i++)
    {
        builder->get_widget(ROTATE_NAMES[i], rotate_btns[i]);
        rotate_btns[i]->signal_clicked().connect(sigc::bind<char, char>(sigc::mem_fun(*this,
                        &myApplication::on_button_clicked), ROTATE, i));
    }

    builder->get_widget("move_entry", move_entry);
    builder->get_widget("scale_entry", scale_entry);
    builder->get_widget("rotate_entry", rotate_entry);


}

// command - move, scale, rotate, code - right, left, up, etc. (look app_codes.h)
void myApplication::on_button_clicked(const char command, const char code)
{
    double value = 0;
    switch (command)
    {
        case MOVE:
            if (read_entry(*move_entry, value))
                // Something like error message?
                return;
            if (move_command(code, value))
                return;
            break;

        case SCALE:
            if (read_entry(*scale_entry, value))
                // Something like error message?
                return;
            if (scale_command(code, value))
                return;
            break;

        case ROTATE:
            if (read_entry(*rotate_entry, value))
                // Something like error message?
                return;
            if (rotate_command(code, value))
                return;
            break;

        default:
            // Error state.
            return;
    }
}

Gtk::Window * myApplication::get_window()
{
    return main_window;
}


err_t myApplication::read_entry(Gtk::Entry &entry, double &value)
{
    std::string str = static_cast<std::string>(entry.get_buffer()->get_text());
    try
    {
        value = std::stod(str);
    } 
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    }
    return OK;
}


bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    std::cout<<"here\n";
    return true;
}


myApplication::~myApplication()
{
    destroy_parr();
}
