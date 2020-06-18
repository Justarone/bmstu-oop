#include "cabin.h"

#include <QDebug>
#include <QString>


Cabin::Cabin(QObject *parent) : QObject(parent),
      _floor(static_cast<short>(Constants::START_FLOOR)),
      _destination(static_cast<short>(Constants::NO_DESTINATION_FLOOR)),
      _state(CabinState::STAND), _direction(Direction::STAND) {

    QObject::connect(this, SIGNAL(stopped(short)), &_doors, SLOT(open()));
    QObject::connect(this, SIGNAL(getReady()), &_doors, SLOT(getReadyToMove()));
    QObject::connect(this, SIGNAL(stop()), this, SLOT(stand()));

    _moveTimer.setSingleShot(true);
    _moveTimer.setInterval(static_cast<size_t>(Times::FLOOR_MOVE));

    QObject::connect(&_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    QObject::connect(&_doors, SIGNAL(closed()), this, SLOT(move()));
}


void Cabin::move() {
    if (_state != CabinState::ACTIVE && _state != CabinState::MOVE)
        return;

    if (_state == CabinState::MOVE) {
        if (_floor != _destination) {
            emit passingFloor(_floor);
            _floor += static_cast<short>(_direction);
            _moveTimer.start();
        }
        else
            emit stop();
    }

    else {
        _state = CabinState::MOVE;
        if (_floor == _destination)
            emit stop();
        else {
            _direction = _destination > _floor ? Direction::UP : Direction::DOWN;
            _moveTimer.start();
        }
    }
}


void Cabin::stand() {
    if (_state != CabinState::MOVE)
        return;

    _state = CabinState::STAND;
    _direction = Direction::STAND;

    qDebug("Elevator stands on the floor %d", _floor);
    emit stopped(_floor);
}


void Cabin::setDestination(short floor) {
    if (_state == CabinState::STAND)
        _state = CabinState::ACTIVE;

    _destination = floor;
    _direction = _destination > _floor ? Direction::UP : Direction::DOWN;

    emit getReady();
}
