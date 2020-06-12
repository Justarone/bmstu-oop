#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <vector>

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
    void setDestinationFloor(short floor);

   private:

    short _curFloor;
    vector<bool> _floors;
    ControllerState _state;
};

#endif // CONTROLLER_H
