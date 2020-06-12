#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QTimer>

#include "constants.h"

enum class DoorsState
{
    OPENED,
    CLOSING,
    CLOSED,
    OPENING
};

class Doors : public QObject
{
    Q_OBJECT

   public slots:
    void open();
    void close();
    void moveToCall();

   public:
    explicit Doors(QObject *parent = nullptr);

   signals:
    void closed();
    void opened();

   private slots:
    void _open();
    void _close();

   private:

    DoorsState _state;
    QTimer _openTimer;
    QTimer _closeTimer;
    QTimer _openedTimer;
};

#endif // DOOR_H
