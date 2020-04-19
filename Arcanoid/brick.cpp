#include <iostream>
#include "constants.h"
#include "brick.h"

Brick::Brick(int x, int y)
    :   m_destroyed{false}
    ,   m_image{"brick.png"}
    ,   m_rect{m_image.rect()}
{
    m_rect.translate(x, y);
}

Brick::~Brick() {
    std::cout << "Brick deleted\n";
}

void Brick::setDestroyed(bool destroyed) { m_destroyed = destroyed; }
void Brick::setRect(QRect rect) { m_rect = rect; }

bool Brick::isDestroyed() const { return m_destroyed; }
QRect Brick::getRect() const { return m_rect; }
QImage Brick::getImage() const { return m_image; }
