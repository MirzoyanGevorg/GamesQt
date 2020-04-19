#include <iostream>
#include "constants.h"
#include "paddle.h"

Paddle::Paddle()
    :   m_image{"paddle.png"}
    ,   m_rect{m_image.rect()}
    ,   m_x{0}
{
    resetState();
}

Paddle::~Paddle() {
    std::cout << "Paddle Deleted\n";
}

void Paddle::move() {
    int x = m_rect.x() + m_x;
    int y = m_rect.top();

    m_rect.moveTo(x, y);
}

void Paddle::resetState() {
    m_rect.moveTo(constants::paddleX, constants::paddleY);
}

void Paddle::setX(int x) { m_x = x; }
QRect Paddle::getRect() const { return m_rect; }
QImage Paddle::getImage() const{ return m_image; }
