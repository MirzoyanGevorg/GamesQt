#ifndef PADDLE_H
#define PADDLE_H

#include <QImage>
#include <QRect>

class Paddle {

    QImage m_image;
    QRect m_rect;
    int m_x;

public:
    Paddle();
    ~Paddle();

public:
    void move();
    void resetState();
    void setX(int x);
    QRect getRect() const;
    QImage getImage() const;
};

#endif // PADDLE_H
