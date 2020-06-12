#include "door.h"
#include "qdebug.h"

Doors::Doors(QObject *parent) : QObject(parent), _state(DoorsState::CLOSED)
{
    _openTimer.setSingleShot(true);
    QObject::connect(&_openTimer, SIGNAL(timeout()), this, SLOT(open()));

    _openedTimer.setInterval(static_cast<int>(Times::DOORS_WAIT));
    _openedTimer.setSingleShot(true);
    // doorIsOpened можно оставить, чтобы расширить с следующих дополнениях
    QObject::connect(
        this, SIGNAL(doorIsOpened()), &_openedTimer, SLOT(start()));
    QObject::connect(
        &_openedTimer, SIGNAL(timeout()), this, SLOT(startClosing()));

    _closeTimer.setSingleShot(true);
    QObject::connect(&_closeTimer, SIGNAL(timeout()), this, SLOT(close()));
}

// Переход в это состояние только из состояния Closed
// Исправлено
void Doors::open()
{
    if (_state != DoorsState::CLOSED)
        return;

    _state = DoorsState::OPENING;
    qDebug("Doors are opening...");
    _openTimer.start(static_cast<int>(Times::DOORS_MOVE));
}

void Doors::_open()
{
    if (_state != DoorsState::OPENING)
        return;
    _state = DoorsState::OPENED;
    qDebug("Doors are opened.");
    emit opened();
}

void Doors::moveToCall()
{
    if (_state == DoorsState::CLOSED)
        emit closed();
}

// Теперь двери закрываются только из состояния "открыты"
void Doors::close()
{
    if (_state != DoorsState::OPENED)
        return;

    _state = DoorsState::CLOSING;
    qDebug("Doors are closing...");
    _closeTimer.start(static_cast<int>(Times::DOORS_MOVE));
}


void Doors::_close()
{
    if (_state != DoorsState::CLOSING)
        return;

    _state = DoorsState::CLOSED;
    qDebug("Doors are closed.");
    emit closed();
}
