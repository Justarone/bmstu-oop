#include "controller.h"

#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent),
      _curFloor(static_cast<int>(Constants::START_FLOOR)),
      _floors(static_cast<size_t>(Constants::FLOORS_AMOUNT), false),
      _state(ControllerState::FREE), _direction(Direction::STAND) {}


// ok
void Controller::setTarget(short floor)
{
    _queue.push_back(floor);
    _state = ControllerState::BUSY;
    _floors[floor - 1] = true;

    _curTarget = _getClosestTarget();
    _direction = _curTarget > _curFloor ? Direction::UP : Direction::DOWN;

    emit setDestination(_curTarget);
}


// ok
void Controller::onFloor(short floor)
{
    if (_state != ControllerState::BUSY)
        return;

    _curFloor = floor;
    _direction = Direction::STAND;
    _floors[floor - 1] = false;

    _curTarget = _getClosestTarget();

    if (_curTarget != static_cast<short>(Constants::NO_DESTINATION_FLOOR))
        emit setDestination(_curTarget);
    else
        _state = ControllerState::FREE;
}

// ok
void Controller::passedFloor(short floor)
{
    _curFloor = floor;
    qDebug("Passing floor %d", _curFloor);
}

// ok
short Controller::_getUpwards() {
    short noFloor = static_cast<short>(Constants::NO_DESTINATION_FLOOR);
    short newFloor = noFloor;
    short floorAmount = static_cast<short>(Constants::FLOORS_AMOUNT);

    for (short i = _curFloor; newFloor == noFloor && i < floorAmount; i++)
        if (_floors[i])
            newFloor = i + 1;
    if (newFloor == static_cast<short>(Constants::NO_DESTINATION_FLOOR))
        newFloor = _queue[0];
    return newFloor;
}


// ok
short Controller::_getDownwards() {
    short noFloor = static_cast<short>(Constants::NO_DESTINATION_FLOOR);
    short newFloor = noFloor;
    for (short i = _curFloor - 2; newFloor == noFloor && i >= 0; i--)
        if (_floors[i])
            newFloor = i + 1;
    if (newFloor == noFloor)
        newFloor = _queue[0];
    return newFloor;
}


// ok
short Controller::_getClosestTarget() {
    _correctQueue();
    if (_queue.size() == 0)
        return static_cast<short>(Constants::NO_DESTINATION_FLOOR);

    if (_direction == Direction::UP) {
        return _getUpwards();
    }

    else if (_direction == Direction::DOWN) {
        return _getDownwards();
    }

    // since here direction == stand
    else if (_curFloor < _queue[0])
        return _getUpwards();

    else
        return _getDownwards();
}


// ok (corrected)
void Controller::_correctQueue() {
    vector<bool> &floorsCopy = _floors;
    auto it = remove_if(_queue.begin(), _queue.end(), [floorsCopy](short elem) {
        return !floorsCopy[elem - 1];
    });
    _queue.erase(it, _queue.end());
}
