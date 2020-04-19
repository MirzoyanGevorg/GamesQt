#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>

class Brick {

    bool m_destroyed;
    QImage m_image;
    QRect m_rect;

public:
    Brick(int x, int y);
    ~Brick();

public:
    void setDestroyed(bool destroyed);
    void setRect(QRect rect);
    bool isDestroyed() const;
    QRect getRect() const;
    QImage getImage() const;
};

#endif // BRICK_H
