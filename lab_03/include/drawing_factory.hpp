#pragma once

#include "drawer.hpp"

class BaseDrawingFactory {
public:
    virtual shared_ptr<BaseDrawer> createDrawer() = 0;
};


class GtkDrawingFactory: public BaseDrawingFactory {
    const Cairo::RefPtr<Cairo::Context> &_cr;
    shared_ptr<BaseDrawer> _drawer;
public:
    explicit GtkDrawingFactory(const Cairo::RefPtr<Cairo::Context> &_cr);
    virtual shared_ptr<BaseDrawer> createDrawer() override;
};
