#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include "SDL2/SDL.h"
#include "SDL2/SDL_joystick.h"
#include "QDebug"
#include "QThread"
#include <QTimer>

class Joystick : public QObject
{
    Q_OBJECT

private:
    SDL_Joystick *myJoystick;
public:
    explicit Joystick(QObject *parent = nullptr);

signals:

public slots:
};

#endif // JOYSTICK_H
