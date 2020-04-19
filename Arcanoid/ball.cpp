#include <iostream>
#include "constants.h"
#include "ball.h"

Ball::Ball()
    :   m_x{1}
    ,   m_y{-1}
    ,   m_image{"ball.png"}
    ,   m_rect{m_image.rect()}
{
    resetState();
}
Ball::~Ball() {
    std::cout << "Ball Deleted\n";
}

void Ball::resetState() {
    m_rect.moveTo(constants::ballX, constants::ballY);
}

void Ball::autoMove() {
    m_rect.translate(m_x, m_y);

    if(m_rect.left() == 0) {
        m_x = 1;
    }

    if(m_rect.right() == constants::rightEdge) {
        m_x = -1;
    }

    if(m_rect.top() == 0) {
        m_y = 1;
    }
}

void Ball::setX(int x) { m_x = x; }
void Ball::setY(int y) { m_y = y; }

int Ball::getX() const { return m_x; }
int Ball::getY() const { return m_y; }
QRect Ball::getRect() const { return m_rect; }
QImage Ball::getImage() const { return m_image; }
