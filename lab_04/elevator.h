#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QTextEdit>

#include "cabin.h"
#include "controller.h"
#include "constants.h"

class Elevator : public QObject
{
    Q_OBJECT

   public:
    Elevator();
    void call(short floor);

   private:
    Controller _controller;
    Cabin _cabin;
};

#endif // ELEVATOR_H
