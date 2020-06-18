#include "elevator.h"

Elevator::Elevator()
{
    QObject::connect(&_controller, SIGNAL(setDestination(short)), &_cabin, SLOT(setDestination(short)));
    QObject::connect(&_cabin, SIGNAL(passingFloor(short)), &_controller, SLOT(passedFloor(short)));
    QObject::connect(&_cabin, SIGNAL(stopped(short)), &_controller, SLOT(onFloor(short)));
}

void Elevator::call(short floor)
{
    _controller.setTarget(floor);
}
