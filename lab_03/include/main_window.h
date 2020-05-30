#pragma once
#include <iostream>
#include <gtkmm-3.0/gtkmm.h>
#include <cairomm-1.0/cairomm/cairomm.h>

class mainWindow
{
    public:
        mainWindow() = delete;
        mainWindow(const char *filename);
        Gtk::Window *get_window();
    protected:
        Gtk::Window *appWindow;
        Gtk::RadioButton *sceneRadio, *modelRadio, *cameraRadio;
        Gtk::DrawingArea *sceneWindow;
        Gtk::Button *prevButton, *nextButton;
        Gtk::Entry *moveXEntry, *moveYEntry, *moveZEntry, *scaleEntry, *rotateEntry;
        Gtk::RadioButton *rotateXRadio, *rotateYRadio, *rotateZRadio;
        Gtk::Button *moveButton, *rotateButton, *scaleButton;
        Gtk::Button *addButton, *removeButton;
        Gtk::Button *loadButton;
        Gtk::Entry *loadEntry;
        void callbackFunction(const char *str);
        bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr);
};
