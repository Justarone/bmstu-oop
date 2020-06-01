#pragma once

class BaseDrawingFactory {
public:
    virtual shared_ptr<BaseDrawer> createDrawer() = 0;
};

class GtkDrawingFactory: public BaseDrawingFactory {
    Gtk::DrawingArea da;
public:
    virtual shared_ptr<BaseDrawer> createDrawer() override;
};
