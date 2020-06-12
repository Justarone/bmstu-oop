#ifndef CABIN_H
#define CABIN_H

#include <QObject>

#include "controller.h"
#include "constants.h"
#include "door.h"

enum class CabinState
{
    MOVE,
    SYNC,
    STAND
};

class Cabin : public QObject
{
    Q_OBJECT

   public slots:
    void move();
    void stand();
    void call(short floor); // Убрать direction отсюда к чертям собачьим

   public:
    explicit Cabin(QObject *parent = nullptr);

   signals:
    void cabinIsCalled();
    void cabinPassingFloor(short floor); // Убрать direction
    void cabinReachedDestinationFloor(short floor);
    void cabinStopped(short floor);

   private:

    Doors _doors;
    short _floor;
    short _destination;
    CabinState _state;
    Direction _direction;
    QTimer _moveTimer;
};

#endif // CABIN_H
