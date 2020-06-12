#include "cabin.h"

#include <QDebug>
#include <QString>

Cabin::Cabin(QObject *parent)
    : QObject(parent),
      _floor(static_cast<short>(Constants::START_FLOOR)),
      _destination(static_cast<short>(Constants::NO_DESTINATION_FLOOR)),
      _state(CabinState::STAND),
      _direction(Direction::STAND) {
    QObject::connect(this, SIGNAL(cabineStopped(short)), &_doors,
                     SLOT(startOpening()));
    QObject::connect(this, SIGNAL(cabineIsCalled()), &_doors, SLOT(moveToCall()));

    QObject::connect(this, SIGNAL(cabineReachedDestinationFloor(short)), this,
                     SLOT(cabineStand()));

    _moveTimer.setSingleShot(true);
    QObject::connect(&_moveTimer, SIGNAL(timeout()), this,
                     SLOT(cabineMoves()));

    QObject::connect(&_doors, SIGNAL(doorIsClosed()), this, SLOT(cabineMoves()));
}


// Тотальный бардак. Проходить все этажи сразу нельзя.
// Исправлено
void Cabin::move() {
    if (_state != CabinState::SYNC && _state != CabinState::MOVE)
        return;

    if (_state == CabinState::MOVE) {
        if (_floor != _destination) {
            emit cabinPassingFloor(_floor);
            _floor += _direction;
            _moveTimer.start(static_cast<size_t>(Times::FLOOR_MOVE));
        } else
            emit cabinReachedDestinationFloor(_floor);
    } else {
        _state = CabinState::MOVE;
        // В этом случае требуется пройти полный цикл, чтобы не нарушать
        // закономерности, несмотря на аллогичность движения стоящей кабины
        if (_floor == _destination)
            emit cabinReachedDestinationFloor(_floor);
        else {
            if (_destination > _floor)
                _direction = Direction::UP;
            else
                _direction = Direction::DOWN;
            _moveTimer.start(static_cast<size_t>(Times::FLOOR_MOVE));
        }
    }
}

void Cabin::stand() {
    if (_state != CabinState::MOVE)
        return;

    _state = CabinState::STAND;
    qDebug("Lift stands on the floor %d", _floor);
    emit cabinStopped(_floor);
}

// Добавлена обработка перехода только из состояния стоит
void Cabin::call(short floor) {
    if (_state != CabinState::STAND)
        return;

    _state = CabinState::SYNC;
    _destination = floor;

    emit cabinIsCalled();
}
