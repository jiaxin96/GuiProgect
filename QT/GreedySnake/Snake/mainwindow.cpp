#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
//    QTime t;
//    t= QTime::currentTime();
//    qsrand(t.msec()+t.second()*1000);
    qsrand(time(NULL));

    int head_x = MASH_COLUMN / 2;
    int head_y = MASH_ROW / 2;

    snakeBody.append(QPoint(head_x, head_y));

    generateOneFood();

    this->setMaximumSize(800,600);
    this->setMinimumSize(800,600);


    QPalette pat;
    pat.setColor(QPalette::Window,QColor("black"));
    this->setPalette(pat);

    this->beginBnt = new QPushButton(this);
    beginBnt->setGeometry(QRect(650,50, 100, 50));
    beginBnt->setText("Start");

    this->exitBnt = new QPushButton(this);
    exitBnt->setGeometry(QRect(650,500, 100, 50));
    exitBnt->setText("Exit");


    score = 0;
    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(19);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);

    this->scoreMess = new QLabel("Score: ", this);
    scoreMess->setFont(font);
    scoreMess->setGeometry(QRect(650,250,60,100));
    scoreMess->setPalette(pe);

    this->scoreCount = new QLabel(this);
    scoreCount->setFont(font);
    scoreCount->setGeometry(QRect(720,250,50,100));
    scoreCount->setPalette(pe);
    scoreCount->setText(QString::number(score));

    timer=new QTimer(this);
    timer->setInterval(300);


    // 信号和槽
    connect(timer,SIGNAL(timeout()),this,SLOT(timeIntervalOffAction()));
    connect(beginBnt,SIGNAL(clicked()), this, SLOT(startButSolt()) );
    connect(exitBnt, SIGNAL(clicked()), this, SLOT(exitButSolt()));

    connect(this, SIGNAL(upGoingSingal()), this, SLOT(upGoingSolt()));
    connect(this, SIGNAL(downGoingSingal()), this, SLOT(downGoingSolt()));
    connect(this, SIGNAL(leftGoingSingal()), this, SLOT(leftGoingSolt()));
    connect(this, SIGNAL(rightGoingSingal()), this, SLOT(rightGoingSolt()));


}

void MainWindow::timeIntervalOffAction() {
    int tempx = snakeBody.front().x();
    int tempy = snakeBody.front().y();
    switch (headDir) {
    case DIRECTION::UU:
        tempy--;
        break;
    case DIRECTION::DD:
        tempy++;
        break;
    case DIRECTION::LL:
        tempx--;
        break;
    case DIRECTION::RR:
        tempx++;
        break;
    default:
        break;
    }
    if (tempx == food.x() && tempy == food.y()) {
        snakeBody.push_front(QPoint(tempx, tempy));
        generateOneFood();
        head_y = tempy, head_x = tempx;
        score++;
        scoreCount->setText(QString::number(score));
    } else {
        if (conflictWithSelf(tempx, tempy) || conflictWithWall(tempx, tempy)) {
            snakeDie();
        } else {
            snakeBody.push_front(QPoint(tempx, tempy));
            snakeBody.pop_back();
            head_y = tempy, head_x = tempx;
        }
    }
    this->update();
}

bool MainWindow::conflictWithWall(int x, int y) {
    if (x < 0 || x >= MASH_COLUMN) return true;
    if (y < 0 || y >= MASH_ROW) return true;
    return false;
}

bool MainWindow::conflictWithSelf(int x, int y) {
    if (snakeBody.size() == 1) {
        return false;
    }
    for (auto it = snakeBody.begin(); it != snakeBody.end(); ++it) {
        if ((*it).x() == x && (*it).y() == y) return true;
    }
    return false;
}
bool MainWindow::conflictWithSnake(int x, int y) {
    int i = 0;
    for (auto it = snakeBody.begin(); it != snakeBody.end(); ++it, i++) {
        if (i == snakeBody.size() - 2) break;
        if ((*it).x() == x && (*it).y() == y) return true;
    }
    return false;
}

void MainWindow::snakeDie() {
    timer->stop();
    if (QMessageBox::question(this, "GameOver", "Again?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        init();
    } else {
        exitButSolt();
    }
}

void  MainWindow::init() {
    head_x = MASH_COLUMN / 2;
    head_y = MASH_ROW / 2;
    headDir = DIRECTION::RR;
    snakeBody.clear();
    snakeBody.push_front(QPoint(head_x,head_y));
    generateOneFood();
    score = 0;
    scoreCount->setText(QString::number(0));
}

void MainWindow::startButSolt() {
    timer->start();
}
void MainWindow::exitButSolt() {
    delete this;
    exit(0);
}

void MainWindow::upGoingSolt() {
    if (headDir == DIRECTION::DD && snakeBody.size() > 1) {
        return;
    }
    headDir = DIRECTION::UU;
}
void MainWindow::downGoingSolt() {
    if (headDir == DIRECTION::UU && snakeBody.size() > 1) {
        return;
    }
    headDir = DIRECTION::DD;
}

void MainWindow::leftGoingSolt() {
    if (headDir == DIRECTION::RR && snakeBody.size() > 1) {
        return;
    }
    headDir = DIRECTION::LL;
}

void MainWindow::rightGoingSolt() {
    if (headDir == DIRECTION::LL && snakeBody.size() > 1) {
        return;
    }
    headDir = DIRECTION::RR;

}


MainWindow::~MainWindow()
{
    delete beginBnt;
    delete exitBnt;
    delete scoreCount;
    delete scoreMess;
}

void MainWindow::generateOneFood()
{

    int tempx = qrand() % MASH_COLUMN;
    int tempy = qrand() % MASH_ROW;

    while (conflictWithSnake(tempx,tempy)) {
        tempx = qrand() % MASH_COLUMN;
        tempy = qrand() % MASH_ROW;
    }

    food.setX(tempx);
    food.setY(tempy);
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int k = event->key();
    switch (k) {
    case Qt::Key_W:
    case Qt::Key_Up:
        emit this->upGoingSingal();
        qDebug() << "UP key pressed" << endl;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        emit this->leftGoingSingal();
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        emit this->downGoingSingal();
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        emit this->rightGoingSingal();
        break;
    default:
        break;
    }

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);

    QPen pen(Qt::blue);

    painter->setPen(pen);
    for (int i = 0; i <= MASH_COLUMN; i++) {
        painter->drawLine(QPoint(i*MASH_W, 0), QPoint(i*MASH_W, 600));
    }

    for (int i = 0; i <= MASH_ROW; i++) {
        painter->drawLine(QPoint(0, i*MASH_W), QPoint(600 ,i*MASH_W));
    }


    QBrush br(Qt::red);
    painter->setBrush(br);

    painter->drawRect(QRect(food.x()*MASH_W, food.y()*MASH_W, MASH_W, MASH_W));
    br.setColor(Qt::cyan);
    painter->setBrush(br);
    for (auto it = snakeBody.begin(); it != snakeBody.end(); ++it) {
        painter->drawRect(QRect((*it).x()*MASH_W, (*it).y()*MASH_W, MASH_W, MASH_W));
    }

    br.setColor(Qt::yellow);
    painter->setBrush(br);
    painter->drawRect(QRect(snakeBody.front().x()*MASH_W, snakeBody.front().y()*MASH_W, MASH_W, MASH_W));


    delete painter;
}
