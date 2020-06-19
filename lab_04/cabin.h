#ifndef CABIN_H
#define CABIN_H

#include <QObject>

#include "constants.h"
#include "doors.h"

enum class CabinState
{
    MOVE,
    ACTIVE,
    STAND
};

class Cabin : public QObject
{
    Q_OBJECT

public slots:
    void move();
    void stand();
    void setDestination(short floor);

public:
    explicit Cabin(QObject *parent = nullptr);

signals:
    void getReady();
    void passingFloor(short floor);
    void stop();
    void stopped(short floor);

private:
    Doors _doors;
    short _floor;
    short _destination;
    CabinState _state;
    Direction _direction;
    QTimer _moveTimer;
};

#endif // CABIN_H
