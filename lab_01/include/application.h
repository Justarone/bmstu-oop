#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "constants.h"
#include <iostream>
#include "data_processing.h"
#include <gtkmm.h>

// Button groups' sizes.
enum { MOVE_SIZE = 6, SCALE_SIZE = 2, ROTATE_SIZE = 6 };


class myApplication
{
    public:
        myApplication(const char *const filename=FILENAME);
        ~myApplication();
        Gtk::Window *get_window();
    protected:
        Gtk::Window *main_window;
        Gtk::DrawingArea *drawing_area;
        Gtk::Button *move_btns[MOVE_SIZE];
        Gtk::Button *scale_btns[SCALE_SIZE];
        Gtk::Button *rotate_btns[ROTATE_SIZE];
        Gtk::Entry *scale_entry, *rotate_entry, *move_entry;

        err_t read_entry(Gtk::Entry &entry, double &value);
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
        void on_button_clicked(const char command, const char code);
};

#endif
