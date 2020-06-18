#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <vector>
#include <algorithm>

#include "constants.h"

template <typename T>
using vector = std::vector<T>;


enum class ControllerState
{
    FREE,
    BUSY
};

class Controller : public QObject
{
    Q_OBJECT

public slots:
    void onFloor(short floor);
    void passedFloor(short floor);

public:
    explicit Controller(QObject *parent = nullptr);
    void setTarget(short floor);

signals:
    void setDestination(short floor);

private:
    vector<short> _queue;
    short _curFloor;
    short _curTarget;
    vector<bool> _floors;
    ControllerState _state;
    Direction _direction;

    void _correctQueue();
    short _getClosestTarget();
    short _getUpwards();
    short _getDownwards();
};

#endif // CONTROLLER_H
