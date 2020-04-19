#include <QPainter>
#include <QApplication>
#include "arcanoid.h"

Arcanoid::Arcanoid(QWidget* parent)
    :   QWidget(parent)
    ,   m_x{0}
    ,   m_gameOver{false}
    ,   m_gameWon{false}
    ,   m_started{false}
    ,   m_paused{false}
    ,   m_ball{new Ball()}
    ,   m_paddle{new Paddle()}
{

    int index = 0;

    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 6; ++j) {
            m_bricks[index] = new Brick(j * 40 + 30, i * 10 + 50);
            ++index;
        }
    }
}

Arcanoid::~Arcanoid() {
    delete m_ball;
    delete m_paddle;

    for(int i{0}; i < constants::brickCount; ++i){
        delete m_bricks[i];
    }
}

void Arcanoid::startGame() {

    if(!m_started) {
        m_ball -> resetState();
        m_paddle -> resetState();

        for(int i{0}; i< constants::brickCount; ++i) {
            m_bricks[i] -> setDestroyed(false);
        }

        m_gameOver = false;
        m_gameWon = false;
        m_started = true;
        m_timerId = startTimer(constants::delay);
    }
}

void Arcanoid::stopGame() {
    killTimer(m_timerId);
    m_gameOver = true;
    m_started = false;
}

void Arcanoid::pauseGame() {
    if(m_paused) {
        m_timerId = startTimer(constants::delay);
        m_paused = false;
    } else {
        m_paused = true;
        killTimer(m_timerId);
    }
}

void Arcanoid::victory() {
    killTimer(m_timerId);
    m_gameWon = true;
    m_started = false;
}

void Arcanoid::checkCollision() {
    if(m_ball -> getRect().bottom() == constants::bottomEdge) {
        stopGame();
    }

    for(int i{0}, count{0}; i < constants::brickCount; ++i) {
        if(m_bricks[i] -> isDestroyed()) {
            ++count;
        }
        if(count == constants::brickCount){
            victory();
        }
    }

    if((m_ball -> getRect()).intersects(m_paddle -> getRect())) {
        int paddlePosL{m_paddle->getRect().left()};
        int ballPosL{m_ball->getRect().left()};

        int first{paddlePosL + 8};
        int second{paddlePosL + 16};
        int third{paddlePosL + 24};
        int fourth{paddlePosL + 32};

        if(ballPosL < first) {
            m_ball -> setX(-1);
            m_ball -> setY(-1);

        } else if(ballPosL >= first && ballPosL < second) {
            m_ball -> setX(-1);
            m_ball -> setY(-1 * m_ball -> getY());

        } else if(ballPosL >= second && ballPosL < third) {
            m_ball -> setX(0);
            m_ball -> setY(-1);

        } else if(ballPosL >= third && ballPosL < fourth) {
            m_ball -> setX(1);
            m_ball -> setY(-1 * m_ball -> getY());

        } else if(ballPosL > fourth) {
            m_ball -> setX(1);
            m_ball -> setY(-1);
        }
    }

    for(int i{0}; i < constants::brickCount; ++i) {
        if((m_ball -> getRect()).intersects(m_bricks[i] -> getRect())) {
            int ballLeft{m_ball->getRect().left()};
            int ballHeight{m_ball->getRect().height()};
            int ballWidth{m_ball->getRect().width()};
            int ballTop{m_ball->getRect().top()};

            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

            if (!m_bricks[i]->isDestroyed()) {
                if(m_bricks[i]->getRect().contains(pointRight)) {
                   m_ball->setX(-1);

                } else if(m_bricks[i]->getRect().contains(pointLeft)) {
                   m_ball->setX(1);

                } else if(m_bricks[i]->getRect().contains(pointTop)) {
                   m_ball->setY(1);

                } else if(m_bricks[i]->getRect().contains(pointBottom)) {
                   m_ball->setY(-1);

                }

                m_bricks[i]->setDestroyed(true);
            }
        }
    }
}

void Arcanoid::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    if(m_gameOver) {
        finishGame(&painter, "Game Over");
    } else if(m_gameWon) {
        finishGame(&painter, "Victory");
    } else {
        drawObjects(&painter);
    }
}

void Arcanoid::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    moveObjects();
    checkCollision();
    repaint();
}

void Arcanoid::keyReleaseEvent(QKeyEvent* event) {
    int x{0};

    switch (event -> key()) {
        case Qt::Key_Left:
            x = 0;
            m_paddle -> setX(x);
            break;
        case Qt::Key_Right:
            x = 0;
            m_paddle -> setX(x);
            break;
    }
}

void Arcanoid::keyPressEvent(QKeyEvent* event) {
    int x{0};

    switch (event -> key()) {
        case Qt::Key_Left:
            x = -1;
            m_paddle -> setX(x);
            break;
        case Qt::Key_Right:
            x = 1;
            m_paddle -> setX(x);
            break;
        case Qt::Key_Pause:
            pauseGame();
            break;
        case Qt::Key_Space:
            startGame();
            break;
        case Qt::Key_Escape:
            qApp -> exit();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void Arcanoid::drawObjects(QPainter* painter) {
    painter -> drawImage(m_ball -> getRect(), m_ball -> getImage());
    painter -> drawImage(m_paddle -> getRect(), m_paddle -> getImage());

    for(int i = 0; i < constants::brickCount; ++i) {
        if(!m_bricks[i] -> isDestroyed()) {
            painter -> drawImage(m_bricks[i] -> getRect(), m_bricks[i] -> getImage());
        }
    }
}

void Arcanoid::moveObjects() {
    m_ball -> autoMove();
    m_paddle -> move();
}

void Arcanoid::finishGame(QPainter *painter, const QString &msg) {
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(msg);

    painter->setFont(font);
    int h = height();
    int w = width();

    painter->translate(QPoint(w/2, h/2));
    painter->drawText(-textWidth/2, 0, msg);
}
