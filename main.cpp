#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QKeyEvent>
#include <QtWidgets>

snakePart ::snakePart(int x, int y)
{
    this-> x = x; this->y = y;
}
int snakePart :: getX()
{
    return x;
}
int snakePart :: getY()
    {
        return y ;
    }

    void snakePart :: draw()
    {

    }


food :: food (int x,int y)
{
    this->x = x; this->y = y;
}

    int food :: getX()
    {
        return x;
    }
    int food :: getY()
    {
        return y ;
    }

    void food :: draw()
    {

    }


    snake::snake()
    {
        dir = Right;
        for(int i = 0 ; i <= 3 ; i++){
            snakePart s = snakePart(COLUMNS/2,ROWS/2);
            body.insert(i,s);
        }
    }
    void snake :: move()
    {
        body.removeAt(body.size()-1);
        grow();
    }
    void snake :: grow()
    {
        snakePart head = (snakePart)body.at(0);
        int x = head.getX();
        int y = head.getY();
        int x1,y1;
        snakePart s(0,0);
        switch(dir)
        {
        case Right:
            x1 = (x+1==COLUMNS)?0:x+1;
            s = snakePart(x1,y);
            break;
        case Left:
            x1 = (x-1==-1)?COLUMNS-1:x-1;
            s = snakePart(x1,y);
            break;
        case Up:
            y1 = (y-1==-1)?ROWS-1:y-1;
            s = snakePart(x,y1);
            break;
        case Down:
            y1 = (y+1==ROWS)?0:y+1;
            s = snakePart(x,y1);
        }
        body.insert(0, s);
    }
    bool snake :: collide(int x, int y, int start)
    {
        for (int i = start; i < body.size();i++) {
            snakePart s1 = body.at(i);
            if(s1.getX() == x && s1.getY() == y)
                return true;
        }
        return false;
    }
   void snake :: setDirection(Direction d1){
            if(d1!=getOppDirection(this -> dir))
                this -> dir = d1;
        }
   int snake :: getHeadX(){ return ((snakePart)body.at(0)).getX();}
   int snake :: getHeadY(){ return ((snakePart)body.at(0)).getY();}
   void draw(QPainter painter)
   {

   }
   Direction snake :: getOppDirection(Direction d){
           Direction d1 = Right;
           switch(d){
               case Right:
                   d1 = Left;
                   break;
               case Left:
                   d1 = Right;
                   break;
               case Up:
                   d1 = Down;
                   break;
               case Down:
                   d1 = Up;
                   break;
           }
           return d1;
       }
MainWindow:: MainWindow(QWidget *parent)
    {
        s = snake();
        GV = new GameView(parent);
        myJoystick = new Joystick();
        event = new SDL_Event();
        setGeometry(100,100,800,600);
        setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
   //     GV->show();
        setEnabled( true );
        setFocusPolicy( Qt::StrongFocus );
        f = new food(0,0);
        *f = GenerateFood();
        timer = new QTimer();
        timer -> setInterval(DELAY);
        timer -> start();
        connect(timer,SIGNAL(timeout()),this,SLOT(test()));
        connect(GV,SIGNAL(someFunction()),this,SLOT(fixDirection()));
        connect(timer,SIGNAL(timeout()),this,SLOT(joystick_update()));
    }
snake MainWindow::getSnake()
{
    return s;
}
void MainWindow ::eatFood()
{
    *f =GenerateFood();
    s.grow();
}

Direction GameView::getDirection()
{
    return d;
}
void MainWindow::fixDirection()
{
    s.setDirection(GV->getDirection());
}
GameView::GameView(QWidget *parent){parent = parent;}
/*---------------------------------------------------------*/


food MainWindow :: GenerateFood()
{
    srand(0);
    int x = rand() % COLUMNS;
    int y = rand() % ROWS;
    while(s.collide(x, y, 0)){
        x = rand()%COLUMNS;
        y = rand()%ROWS;
    }
    return food(x,y);
}
    void MainWindow :: test()
    {
        s.move();
        if(s.collide(f -> getX(), f -> getY(), 0))
              eatFood();
        if(s.collide(s.getHeadX(),s.getHeadY(),1))
        {
            timer->stop();
            exit(0);
        }
        repaint();
    }
    void MainWindow :: paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);

        for (int i = 0; i < s.body.size() ; i++)
        {
            if(i == 0)
                painter.setPen(QPen(Qt::blue, 12, Qt::SolidLine, Qt::RoundCap));
            else {
                painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
            }
            snakePart s1 = (snakePart)s.body.at(i);
            painter.drawEllipse(LENGTH*s1.getX(),LENGTH*s1.getY(),LENGTH,LENGTH);
        }
        painter.setPen(QPen(Qt::red, 12, Qt::SolidLine, Qt::RoundCap));
        painter.drawEllipse(f->getX()*LENGTH,LENGTH*f->getY(),LENGTH/2,LENGTH/2);
    }
    void MainWindow::joystick_update()
    {
        while(SDL_PollEvent(event))
        {
            if(event->type == SDL_JOYAXISMOTION)
            {
                if(event->jaxis.axis == 0)
                {
                    if(event->jaxis.value > 0)
                        s.setDirection(Right);
                    else if(event->jaxis.value < 0)
                        s.setDirection(Left);
                }
                else if(event->jaxis.axis == 1)
                {
                    if(event->jaxis.value > 0)
                        s.setDirection(Down);
                    else if(event->jaxis.value < 0)
                        s.setDirection(Up);
                }
            }
            else if(event->type == SDL_JOYBUTTONDOWN)
            {
                if(event->jbutton.button == 5)
                    timer->setInterval(MAX_DELAY);
            }
            else if(event->type == SDL_JOYBUTTONUP)
            {
                if(event->jbutton.button == 5)
                    timer->setInterval(DELAY);
            }
        }
    }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
