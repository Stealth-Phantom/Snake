#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define LENGTH 20
#define ROWS 30
#define COLUMNS 40
#define DELAY 200
#define MAX_DELAY 30


#include <QMainWindow>
#include <QVector>
#include <QPainter>
#include "qdebug.h"
#include <QGraphicsView>
#include <joystick.h>

enum Direction{Right,Left,Up,Down};

namespace Ui {
class MainWindow;
};

class snakePart {

private :
    int x,y;
public:
    snakePart(int x, int y);

    int getX();
    int getY();

    void draw();
};

class food {

private :
    int x,y;
public:
    food(int x, int y);
    int getX();
    int getY();
    void draw();
};

class snake
{
public:
    QList <snakePart> body;
    Direction dir;
public:
    snake();
    void move();
    void grow();
    bool collide(int x, int y, int start);
    void setDirection(Direction d1);
    int getHeadX();
    int getHeadY();
    void draw(QPainter painter);
private:
   Direction getOppDirection(Direction d);
};

class GameView : public QWidget
{
    Q_OBJECT
private:
    Direction d;
public:
    GameView(QWidget *parent);

    Direction getDirection();


signals:
    void someFunction();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GameView *GV;
    QTimer *timer;
    snake s;
    food *f;
    Joystick *myJoystick;
    SDL_Event *event;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void eatFood();
    food GenerateFood();
    snake getSnake();


public slots:
    void test();
    void fixDirection();
    void joystick_update();
protected:
    void paintEvent(QPaintEvent *event);
};


#endif // MAINWINDOW_H
