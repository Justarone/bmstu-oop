#pragma once
#include <iostream>
#include <gtkmm-3.0/gtkmm.h>
#include <cairomm-1.0/cairomm/cairomm.h>

#include "facade.hpp"

#define NEXT 1
#define PREV -1

enum class ButtonType {
    PREV_BUTTON,
    NEXT_BUTTON,
    ADD_BUTTON,
    REMOVE_BUTTON,
    MOVE_BUTTON,
    SCALE_BUTTON,
    ROTATE_BUTTON,
    LOAD_BUTTON,
};

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
    void callbackFunction(ButtonType bt);
    bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr);
    double readEntry(const Gtk::Entry &entry);
private:
    AppFacade facade;
};
