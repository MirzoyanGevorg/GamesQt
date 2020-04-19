#ifndef ARCANOID_H
#define ARCANOID_H

#include <QWidget>
#include <QKeyEvent>
#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include "constants.h"

class Arcanoid : public QWidget {

    int m_x;
    int m_timerId;
    bool m_gameOver;
    bool m_gameWon;
    bool m_started;
    bool m_paused;
    Ball* m_ball;
    Paddle* m_paddle;
    Brick* m_bricks[constants::brickCount];

public:
    Arcanoid(QWidget* parent = nullptr);
    ~Arcanoid();

public:
    void startGame();
    void stopGame();
    void pauseGame();
    void victory();
    void checkCollision();

    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void drawObjects(QPainter* painter);
    void moveObjects();
    void finishGame(QPainter* painter, const QString& msg);
};

#endif // ARCANOID_H
