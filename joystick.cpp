#include "joystick.h"

Joystick::Joystick(QObject *parent) : QObject(parent)
{
    SDL_Init(SDL_INIT_JOYSTICK);

    myJoystick = SDL_JoystickOpen(0);
    if(myJoystick == NULL)
    {
        qDebug() << "No joystick connected";
        exit(1);
    }
    qDebug() << SDL_JoystickNumAxes(myJoystick);
    qDebug() << SDL_JoystickNumButtons(myJoystick);

}

