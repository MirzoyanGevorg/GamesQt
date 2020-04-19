#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include "constants.h"

class Snake : public QWidget
{
    QImage m_dot;
    QImage m_head;
    QImage m_apple;

    int m_timerId;
    int m_dots;
    int m_appleX;
    int m_appleY;

    int m_x[constants::allDots];
    int m_y[constants::allDots];

    bool m_left;
    bool m_right;
    bool m_up;
    bool m_down;
    bool m_inGame;

public:
    Snake(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
    void keyPressEvent(QKeyEvent* event);

private:
    void loadImages();
    void initGame();
    void locateApple();
    void checkApple();
    void checkColision();
    void move();
    void doDrawing();
    void gameOver(QPainter& painter);
};

#endif // SNAKE_H
