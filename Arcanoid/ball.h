#ifndef BALL_H
#define BALL_H

#include <QImage>
#include <QRect>

class Ball {

    int m_x;
    int m_y;
    QImage m_image;
    QRect m_rect;

public:
    Ball();
    ~Ball();

public:
    void resetState();
    void autoMove();
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    QRect getRect() const;
    QImage getImage() const;
};

#endif // BALL_H
