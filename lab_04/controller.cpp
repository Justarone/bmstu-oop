#include "controller.h"

#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent),
      _curFloor(static_cast<int>(Constants::START_FLOOR)),
      _floors(static_cast<size_t>(Constants::FLOORS_AMOUNT), false),
      _state(ControllerState::FREE) {}

void Controller::setTarget(short floor)
{
    _state = ControllerState::BUSY;
    _floors[floor - 1] = true;
    emit setDestinationFloor(floor);
}

void Controller::onFloor(short floor)
{
    if (_state != ControllerState::BUSY)
        return;
    _curFloor = floor;
    _floors[floor - 1] = false;

    short newFloor = static_cast<short>(Constants::NO_DESTINATION_FLOOR);
    bool isNewFloorFound = false;
    for (int i = 0; i < static_cast<int>(Constants::FLOORS_AMOUNT) - 1 && !isNewFloorFound; i++)
    {
        if (_floors[i])
        {
            newFloor = i + 1;
            isNewFloorFound = true;
        }
    }

    if (isNewFloorFound)
        emit setDestinationFloor(newFloor);
    else
        _state = ControllerState::FREE;
}

void Controller::passedFloor(short floor)
{
    _curFloor = floor;
    qDebug("It's moving! Now we are at floor %d", _curFloor);
}
