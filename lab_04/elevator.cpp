#include "elevator.h"

Elevator::Elevator()
{
    QObject::connect(&_controller, SIGNAL(setDestinationFloor(short)), &_cabin,
        SLOT(cabineCall(short)));

    QObject::connect(&_cabin, SIGNAL(cabinPassingFloor(short)), &_controller,
        SLOT(passedFloor(short)));

    QObject::connect(&_cabin, SIGNAL(cabinStopped(short)), &_controller,
        SLOT(onFloor(short)));
}

void Elevator::call(short floor)
{
    _controller.setTarget(floor);
}
