#include "doors.h"
#include "qdebug.h"

Doors::Doors(QObject *parent) : QObject(parent), _state(DoorsState::CLOSED)
{
    _openTimer.setSingleShot(true);
    _openTimer.setInterval(static_cast<int>(Times::DOORS_MOVE));
    _closeTimer.setSingleShot(true);
    _closeTimer.setInterval(static_cast<int>(Times::DOORS_MOVE));
    _openedTimer.setSingleShot(true);
    _openedTimer.setInterval(static_cast<int>(Times::DOORS_WAIT));

    QObject::connect(&_openTimer, SIGNAL(timeout()), this, SLOT(_open()));
    QObject::connect(this, SIGNAL(opened()), &_openedTimer, SLOT(start()));
    QObject::connect(&_openedTimer, SIGNAL(timeout()), this, SLOT(close()));
    QObject::connect(&_closeTimer, SIGNAL(timeout()), this, SLOT(_close()));
}

void Doors::open()
{
    if (_state != DoorsState::CLOSED)
        return;

    _state = DoorsState::OPENING;
    qDebug("Doors are opening");
    _openTimer.start();
}

void Doors::_open()
{
    if (_state != DoorsState::OPENING)
        return;

    _state = DoorsState::OPENED;
    qDebug("Doors are opened");
    emit opened();
}

void Doors::getReadyToMove()
{
    if (_state == DoorsState::CLOSED)
        emit closed();
}

void Doors::close()
{
    if (_state != DoorsState::OPENED)
        return;

    _state = DoorsState::CLOSING;
    qDebug("Doors are closing");
    _closeTimer.start();
}

void Doors::_close()
{
    if (_state != DoorsState::CLOSING)
        return;

    _state = DoorsState::CLOSED;
    qDebug("Doors are closed");
    emit closed();
}
