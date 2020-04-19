#include <QPainter>
#include <QTime>
#include "snake.h"

Snake::Snake(QWidget* parent)
    : QWidget{parent}
    , m_left{false}
    , m_right{true}
    , m_up{false}
    , m_down{false}
    , m_inGame{true}
{
    setStyleSheet("background-color:black;");

    resize(constants::boardWidth, constants::boardHeight);
    loadImages();
    initGame();
}

void Snake::loadImages() {
    m_dot.load("dot.png");
    m_head.load("head.png");
    m_apple.load("apple.png");
}

void Snake::initGame() {
    m_dots = 3;

    for (int i = 0; i < m_dots; ++i) {
        m_x[i] = 50 - i * 10;
        m_y[i] = 50;
    }

    locateApple();
    m_timerId = startTimer(constants::delay);
}

void Snake::locateApple() {
    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec()));

    int r = qrand() % constants::randPos;
    m_appleX = (r * constants::dotSize);

    r = qrand() % constants::randPos;
    m_appleY = (r * constants::dotSize);
}

void Snake::checkApple() {
    if((m_x[0] == m_appleX) && (m_y[0] == m_appleY)) {
        ++m_dots;
        locateApple();
    }
}

void Snake::checkColision() {
    for(int i = m_dots; i > 0; --i) {
        if((i > 4) && m_x[0] == m_x[i] && m_y[0] == m_y[i]) {
            m_inGame = false;
        }
    }

    if(m_x[0] >= constants::boardWidth) {
        m_inGame = false;
    }

    if(m_x[0] < 0) {
        m_inGame = false;
    }

    if(m_y[0] >= constants::boardHeight) {
        m_inGame = false;
    }

    if(m_y[0] < 0) {
        m_inGame = false;
    }

    if(!m_inGame) {
        killTimer(m_timerId);
    }
}

void Snake::move() {
    for(int i = m_dots; i > 0; --i) {
        m_x[i] = m_x[i - 1];
        m_y[i] = m_y[i - 1];
    }

    if(m_left) {
        m_x[0] -= constants::dotSize;
    }

    if(m_right) {
        m_x[0] += constants::dotSize;
    }

    if(m_up) {
        m_y[0] -= constants::dotSize;
    }

    if(m_down) {
        m_y[0] += constants::dotSize;
    }
}

void Snake::doDrawing() {

    QPainter painter(this);

    if(m_inGame) {
        painter.drawImage(m_appleX, m_appleY, m_apple);
        for(int i = 0; i < m_dots; ++i) {
            if(!i) {
                painter.drawImage(m_x[i], m_y[i], m_head);
            } else {
                painter.drawImage(m_x[i], m_y[i], m_dot);
            }
        }
    } else {
        gameOver(painter);
    }
}

void Snake::gameOver(QPainter &painter) {
    QString msg = "Game Over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fontm(font);
    int textWidth = fontm.width(msg);

    painter.setPen(Qt::white);
    painter.setFont(font);
    int h = height();
    int w = width();

    painter.translate(QPoint(w / 2, h / 2));
    painter.drawText(-textWidth / 2, 0 , msg);
}

void Snake::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    doDrawing();
}

void Snake::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event);
    if(m_inGame) {
        checkApple();
        checkColision();
        move();
    }
    repaint();
}

void Snake::keyPressEvent(QKeyEvent* event) {
    int key = event -> key();

    if((key == Qt::Key_Left) && (!m_right)) {
        m_left = true;
        m_up = false;
        m_down = false;
    }

    if((key == Qt::Key_Right) && (!m_left)) {
        m_right = true;
        m_up = false;
        m_down = false;
    }

    if((key == Qt::Key_Up) && (!m_down)) {
        m_up = true;
        m_left = false;
        m_right = false;
    }

    if((key == Qt::Key_Down) && (!m_up)) {
        m_down = true;
        m_left = false;
        m_right = false;
    }

    QWidget::keyPressEvent(event);
}
