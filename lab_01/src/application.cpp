#include "../include/application.h"
#include <iostream>

static const char *MOVE_NAMES[] = { "move_up", "move_down", "move_right",
    "move_left", "move_front", "move_back" };
static const char *SCALE_NAMES[] = { "scale_plus", "scale_minus" };
static const char *ROTATE_NAMES[] = { "rotate_up", "rotate_down", "rotate_left", 
    "rotate_right", "rotate_rightup", "rotate_leftup" };
static const char *ENTRY_NAMES[] = { "move_entry", "scale_entry", "rotate_entry" };


void my_draw(Gtk::DrawingArea *da, const figure_t &figure);

 
myApplication::myApplication(const char* const filename)
{
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    builder->add_from_file(filename);

    builder->get_widget("main_window", main_window);
    main_window->set_title("Лабораторная №1.");
    Gdk::RGBA color, color2;
    color.set_rgba(0.8, 0.8, 0.8);
    color2.set_rgba(0., 0.15, 0.3);
    main_window->override_background_color(color);

    builder->get_widget("drawing_area", drawing_area);

    for (int i = 0; i < MOVE_SIZE; i++)
    {
        builder->get_widget(MOVE_NAMES[i], move_btns[i]);
        move_btns[i]->signal_clicked().connect(sigc::bind<char, char>(sigc::mem_fun(*this,
                        &myApplication::on_button_clicked), MOVE, i));
        move_btns[i]->override_background_color(color2);
        move_btns[i]->override_color(color);
    }

    for (int i = 0; i < SCALE_SIZE; i++)
    {
        builder->get_widget(SCALE_NAMES[i], scale_btns[i]);
        scale_btns[i]->signal_clicked().connect(sigc::bind<char, char>(sigc::mem_fun(*this,
                        &myApplication::on_button_clicked), SCALE, i));
        scale_btns[i]->override_background_color(color2);
        scale_btns[i]->override_color(color);
    }

    for (int i = 0; i < ROTATE_SIZE; i++)
    {
        builder->get_widget(ROTATE_NAMES[i], rotate_btns[i]);
        rotate_btns[i]->signal_clicked().connect(sigc::bind<char, char>(sigc::mem_fun(*this,
                        &myApplication::on_button_clicked), ROTATE, i));
        rotate_btns[i]->override_background_color(color2);
        rotate_btns[i]->override_color(color);
    }

    for (int i = 0; i < CMD_N; i++)
    {
        builder->get_widget(ENTRY_NAMES[i], entry_arr[i]);
        entry_arr[i]->get_buffer()->set_text("0");
        entry_arr[i]->override_background_color(color2);
        entry_arr[i]->override_color(color);
    }
}

// command - move, scale, rotate, code - right, left, up, etc. (look app_codes.h)
void myApplication::on_button_clicked(const char command, const char code)
{
    double value[CMD_N] = {};
    for (int i = 0; i < CMD_N; i++)
        if (read_entry(*entry_arr[i], value[i]))
            return;

    event_t click_event = init_event(command, code, drawing_area, value);
    err_t rc = task_manager(click_event);

    if (rc)
    {
        event_t error_event = init_event(QUIT, NO_CODE, drawing_area, value);
        task_manager(error_event);
        exit(rc);
    }
    else
    {
        event_t draw_event = init_event(DRAW, NO_CODE, drawing_area, value);
        task_manager(draw_event);
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
        return READ_ERROR;
    }
    return OK;
}


// call this callback with drawing_area->queue_draw()
// connect: drawing_area->signal_draw().connect(sigc::mem_fun(*this, &myApplication::on_draw));
//bool myApplication::on_draw(Cairo::RefPtr<Cairo::Context> const& cr)
//{
    //const figure_t figure = get_figure();
    //cr->set_source_rgb(1., .5, .0);
    //cr->set_line_width(2);

    //for (unsigned int i = 0; i < figure.links.size; i++)
    //{
        //cr->move_to(figure.points.arr[figure.links.arr[i].l1].x,
                //figure.points.arr[figure.links.arr[i].l1].y);
        //cr->line_to(figure.points.arr[figure.links.arr[i].l2].x,
                //figure.points.arr[figure.links.arr[i].l2].y);
    //}

    //cr->stroke();
    //return true;
//}

