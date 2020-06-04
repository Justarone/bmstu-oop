#include "main_window.hpp"
#include <cstring>

mainWindow::mainWindow(const char *filename)
{
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    builder->add_from_file(filename);

    builder->get_widget("appWindow", appWindow);

    builder->get_widget("sceneRadio", sceneRadio);
    builder->get_widget("modelRadio", modelRadio);
    builder->get_widget("cameraRadio", cameraRadio);
    modelRadio->join_group(*sceneRadio);
    cameraRadio->join_group(*sceneRadio);

    builder->get_widget("sceneWindow", sceneWindow);
    sceneWindow->signal_draw().connect(sigc::mem_fun(*this, &mainWindow::on_draw));

    builder->get_widget("prevButton", prevButton);
    builder->get_widget("nextButton", nextButton);

    prevButton->signal_clicked().connect(sigc::bind<ButtonType>(sigc::mem_fun(*this,
                    &mainWindow::callbackFunction), ButtonType::PREV_BUTTON));
    nextButton->signal_clicked().connect(sigc::bind<ButtonType>(sigc::mem_fun(*this,
                    &mainWindow::callbackFunction), ButtonType::NEXT_BUTTON));

    builder->get_widget("moveXEntry", moveXEntry);
    builder->get_widget("moveYEntry", moveYEntry);
    builder->get_widget("moveZEntry", moveZEntry);
    builder->get_widget("rotateEntry", rotateEntry);
    builder->get_widget("scaleEntry", scaleEntry);
    moveXEntry->get_buffer()->set_text("0");
    moveYEntry->get_buffer()->set_text("0");
    moveZEntry->get_buffer()->set_text("0");
    rotateEntry->get_buffer()->set_text("0");
    scaleEntry->get_buffer()->set_text("0");

    builder->get_widget("rotateXRadio", rotateXRadio);
    builder->get_widget("rotateYRadio", rotateYRadio);
    builder->get_widget("rotateZRadio", rotateZRadio);
    rotateYRadio->join_group(*rotateXRadio);
    rotateZRadio->join_group(*rotateXRadio);

    builder->get_widget("moveButton", moveButton);
    builder->get_widget("rotateButton", rotateButton);
    builder->get_widget("scaleButton", scaleButton);
    moveButton->signal_clicked().connect(sigc::bind<ButtonType>(sigc::mem_fun(*this,
                    &mainWindow::callbackFunction), ButtonType::MOVE_BUTTON));
    rotateButton->signal_clicked().connect(sigc::bind<ButtonType>(sigc::mem_fun(*this,
                    &mainWindow::callbackFunction), ButtonType::ROTATE_BUTTON));
    scaleButton->signal_clicked().connect(sigc::bind<ButtonType>(sigc::mem_fun(*this,
                    &mainWindow::callbackFunction), ButtonType::SCALE_BUTTON));


    builder->get_widget("addButton", addButton);
    builder->get_widget("removeButton", removeButton);
    addButton->signal_clicked().connect(sigc::bind<ButtonType>(sigc::mem_fun(*this,
                    &mainWindow::callbackFunction), ButtonType::ADD_BUTTON));
    removeButton->signal_clicked().connect(sigc::bind<ButtonType>(sigc::mem_fun(*this,
                    &mainWindow::callbackFunction), ButtonType::REMOVE_BUTTON));

    builder->get_widget("loadButton", loadButton);
    loadButton->signal_clicked().connect(sigc::bind<ButtonType>(sigc::mem_fun(*this,
                    &mainWindow::callbackFunction), ButtonType::LOAD_BUTTON));
    //any_widget->override_background_color(color2);
    //any_widget->override_color(color);
}

void mainWindow::callbackFunction(ButtonType bt) {
    ObjectType ot = modelRadio->get_active() ? ObjectType::MODEL : (cameraRadio->get_active() ?
            ObjectType::CAMERA : ObjectType::SCENE);

    if (bt == ButtonType::LOAD_BUTTON) {
        Gtk::FileChooserDialog dialog("Please, choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.set_transient_for(*appWindow);

        //Add response buttons the the dialog:
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);

        int result = dialog.run();
        if (result == Gtk::RESPONSE_OK) {
            std::string filename = dialog.get_filename();
            try {
                facade.loadScene(filename.c_str());
            } catch (AppBaseException &err) {
                Gtk::MessageDialog dialog(*appWindow, "Can't load scene");
                dialog.set_secondary_text(err.what());
                dialog.run();
            }
        } else {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text("Something went wrong while you were chosing file.");
            dialog.run();
        }
    }

    else if (bt == ButtonType::ADD_BUTTON) {
        try {
            facade.addComponent(ot);
        } catch (AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
    }

    else if (bt == ButtonType::REMOVE_BUTTON) {
        try {
            facade.removeComponent(ot);
        } catch (AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
    }

    else if (bt == ButtonType::NEXT_BUTTON) {
        try {
            facade.changeComponent(NEXT, ot);
        } catch (AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
    }

    else if (bt == ButtonType::PREV_BUTTON) {
        try {
            facade.changeComponent(PREV, ot);
        } catch (AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
    }
    else if (bt == ButtonType::MOVE_BUTTON) {
        double x, y, z;
        try {
            x = readEntry(*moveXEntry);
            y = readEntry(*moveYEntry);
            z = readEntry(*moveZEntry);
        } catch(AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
        shared_ptr<BaseComponentVisitor> visitor(new MoveVisitor(x, y, z));
        try {
            facade.transformComponent(visitor, ot);
        } catch(AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
    }
    else if (bt == ButtonType::SCALE_BUTTON) {
        double value = 0;
        try {
            value = readEntry(*scaleEntry);
        } catch(AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
        shared_ptr<BaseComponentVisitor> visitor(new ScaleVisitor(value));
        try {
            facade.transformComponent(visitor, ot);
        } catch(AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
    }
    else if (bt == ButtonType::ROTATE_BUTTON) {
        double value = 0;
        try {
            value = readEntry(*rotateEntry);
        } catch(AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
        Direction dir = rotateXRadio->get_active() ? Direction::X : (rotateYRadio->get_active() ?
                Direction::Y : Direction::Z);
        shared_ptr<BaseComponentVisitor> visitor(new RotateVisitor(dir, value));
        try {
            facade.transformComponent(visitor, ot);
        } catch(AppBaseException &err) {
            Gtk::MessageDialog dialog(*appWindow, "Error!");
            dialog.set_secondary_text(err.what());
            dialog.run();
        }
    }

    shared_ptr<BaseDrawingFactory> factoryPtr;
    shared_ptr<BaseProector> proectorPtr;
    auto cr = sceneWindow->get_window()->create_cairo_context();
    factoryPtr.reset(new GtkDrawingFactory(cr));
    proectorPtr.reset(new OrtogonalProector());
    facade.drawScene(factoryPtr, proectorPtr);
}

//==================================== HINT ==========================================================
    //cr->set_source_rgb(1, 1, 1);
    //cr->paint();
    //cr->stroke();
    //cr->set_line_width(5);
    //cr->move_to(x, y)
    //cr->line_to(x, y)
    //cr->stroke_preserve();
//====================================================================================================

Gtk::Window * mainWindow::get_window() {
    return appWindow;
}


double mainWindow::readEntry(const Gtk::Entry &entry) {
    std::string str = static_cast<std::string>(entry.get_buffer()->get_text());
    double value = 0;
    try {
        value = std::stod(str);
    } catch (const std::invalid_argument& ia) {
        throw AppInvalidArgument("Can't convert input to double number.");
    }
    return value;
}

// connect: drawing_area->signal_draw().connect(sigc::mem_fun(*this, &myApplication::on_draw));
bool mainWindow::on_draw(Cairo::RefPtr<Cairo::Context> const& cr) {
    shared_ptr<BaseDrawingFactory> factoryPtr;
    shared_ptr<BaseProector> proectorPtr;
    factoryPtr.reset(new GtkDrawingFactory(cr));
    proectorPtr.reset(new OrtogonalProector());
    facade.drawScene(factoryPtr, proectorPtr);
    return true;
}

