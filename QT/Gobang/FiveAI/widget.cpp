#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setMinimumSize(642, 492);
    setMaximumSize(642, 492);

    this->setWindowTitle(QString::fromUtf8("简单先手五子棋(附AI)"));


    QPalette pat;
    pat.setColor(QPalette::Window,QColor(255, 255, 204));
    this->setPalette(pat);

    QFont f;
    f.setBold(true);
    f.setFamily(QString::fromUtf8("Tahoma"));
    f.setPixelSize(20);
    whichOneTurnMess = new QLabel(this);
    whichOneTurnMess->setFont(f);
    whichOneTurnMess->setGeometry(QRect(492, 221, 70, 50));
    whichOneTurnMess->setText("Turns:");


    whichOneTurn = new QLabel(this);
    whichOneTurn->setFont(f);
    whichOneTurn->setGeometry(QRect(572, 221, 60, 50));


    startFirstBut = new QPushButton(QString::fromUtf8("先手开始") , this);
    startFirstBut->setGeometry(QRect(492, 50, 100, 50));

    startLaterBut = new QPushButton(QString::fromUtf8("后手开始") , this);
    startLaterBut->setGeometry(QRect(492, 150, 100, 50));

    exitBut = new QPushButton(QString::fromUtf8("退出") , this);
    exitBut->setGeometry(QRect(492, 392, 100, 50));


    backOne = new QPushButton(QString::fromUtf8("退一步"), this);
    backOne->setGeometry(QRect(492,280, 100, 50));


    // AI part
    statisticwinWays();
    qDebug() << "AI has been ready!\n";

    init();

    QObject::connect(backOne, SIGNAL(clicked()) , this, SLOT(backOneButClicked()) );
    QObject::connect(startFirstBut, SIGNAL(clicked()), this, SLOT(startFirstButClicked()) );
    QObject::connect(startLaterBut, SIGNAL(clicked()), this, SLOT(startLaterButClicked()) );
    QObject::connect(exitBut, SIGNAL(clicked()), this, SLOT(exitButClicked()) );


    // 使用Design的话会用到 纯代码的话没有什么效果
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete whichOneTurn;
    delete whichOneTurnMess;
    delete startFirstBut;
    delete startLaterBut;
    delete backOne;
    delete exitBut;
    delete ui;
}

void Widget::startFirstButClicked() {
    if (canStart) {
        turns = 2;
        changeTurn();
        firstPlay = true;
        canStart = false;
        gameStart = true;
    }

}



void Widget::startLaterButClicked()
{
    if (canStart) {
        firstPlay = false;
        gameStart = true;
        canStart = false;
        // 后手
        countChess++;
        turns = 1;
        playMap[7][7] = turns;
        currentPoint.setX(7);
        currentPoint.setY(7);
        changeTurn();

        this->update();
    }

}

void Widget::changeTurn() {
    if (turns == 1) {
        turns = 2;
        this->whichOneTurn->setText("White");
    } else {
        turns = 1;
        this->whichOneTurn->setText("Black");
    }
}

void Widget::backOneButClicked() {

    if (gameStart) {
        qDebug() << "Back One Clicked\n";
        if (firstPlay && turns == 1) {
            if (countChess < 2) return;
            countChess -= 2;
            QPoint t = chessLise.back();
            playMap[t.x()][t.y()] = 0;
            chessLise.pop_back();

            for (int i = 0; i < winsWayCount; ++i) {
                if (winsArr[t.x()][t.y()][i]) {
                    computerWinsWayStatisticArr[i]--;
                }
            }

            t = chessLise.back();
            playMap[t.x()][t.y()] = 0;
            chessLise.pop_back();
            for (int i = 0; i < winsWayCount; ++i) {
                if (winsArr[t.x()][t.y()][i]) {
                    playerWinsWayStatisticArr[i]--;
                }
            }
        }
        else if (!firstPlay && turns == 2) {
            if (countChess < 3) return;
            countChess -= 2;
            QPoint t = chessLise.back();
            playMap[t.x()][t.y()] = 0;
            chessLise.pop_back();
            for (int i = 0; i < winsWayCount; ++i) {
                if (winsArr[t.x()][t.y()][i]) {
                    computerWinsWayStatisticArr[i]--;
                }
            }
            t = chessLise.back();
            playMap[t.x()][t.y()] = 0;
            chessLise.pop_back();
            for (int i = 0; i < winsWayCount; ++i) {
                if (winsArr[t.x()][t.y()][i]) {
                    playerWinsWayStatisticArr[i]--;
                }
            }
        }
        this->update();
    }



}

void Widget::exitButClicked()
{
    delete this;
    exit(0);
}



bool Widget::checkWin()
{
    int preTurn = ( turns == 1 ? 2 : 1);
    int cx = currentPoint.x();
    int cy = currentPoint.y();
    int  count = 0;
    // 横向计数
    while (cy >= 0 && playMap[cx][cy] == preTurn) {
        count++;
        cy--;
    }
    cy = currentPoint.y() + 1;
    while (cy < 15 && playMap[cx][cy] == preTurn) {
        count++;
        cy++;
    }
    if (count == 5) {
        return true;
    }


    cx = currentPoint.x();
    cy = currentPoint.y();
    count = 0;
    // 纵向
    while (cx >= 0 && playMap[cx][cy] == preTurn) {
        count++;
        cx--;
    }
    cx = currentPoint.x() + 1;
    while (cx < 15 && playMap[cx][cy] == preTurn) {
        count++;
        cx++;
    }
    if (count == 5) {
        return true;
    }


    cx = currentPoint.x();
    cy = currentPoint.y();
    count = 0;
    // 主对角线
    while (cx >= 0 && cy >= 0 && playMap[cx][cy] == preTurn) {
        cx--;cy--;
        count++;
    }

    cx = currentPoint.x() + 1;
    cy = currentPoint.y() + 1;
    while (cx < 15 && cy < 15 && playMap[cx][cy] == preTurn) {
        cx++;cy++;
        count++;
    }
    if (count == 5) {
        return true;
    }



    cx = currentPoint.x();
    cy = currentPoint.y();
    count = 0;
    // 副对角线
    while (cx >= 0 && cy < 15 && playMap[cx][cy] == preTurn) {
        cx--;cy++;
        count++;
    }
    cx = currentPoint.x() + 1;
    cy = currentPoint.y() - 1;
    while (cx < 15 && cy >= 0 && playMap[cx][cy] == preTurn) {
        cx++;cy--;
        count++;
    }
    if (count == 5) {
        return true;
    }

    return false;
}

void Widget::winShow()
{
    QString str;
    if (turns == 1) {
        str = "White";
    } else {
        str = "Black";
    }
    if (QMessageBox::question(this, str + " Win!!!", "Again?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        init();
    } else {
        exitButClicked();
    }
}

void Widget::init()
{
//    for (int i = 0; i < 15; ++i) {
//        for (int j = 0; j < 15; ++j) {
//            playMap[i][j] = 0;
//        }
//    }
    gameStart = false;
    canStart = true;
    whichOneTurn->setText("Black");

    countChess = 0;

    // 1 表示黑色落子
    // 2  表示白色落子
    turns = 1;


    // AI part
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            playMap[i][j] = 0;
            playerScore[15][15] = 0;
            computerScore[15][15] = 0;
        }
    }

    for (int k = 0; k < winsWayCount; ++k) {
        playerWinsWayStatisticArr[k] = 0;
        computerWinsWayStatisticArr[k] = 0;
    }
    this->update();
//    playMap[7][7] = 2;
//    playMap[7][8] = 1;
}




void Widget::mousePressEvent(QMouseEvent *event)
{
    if (gameStart) {
        if (( firstPlay && turns == 1 ) || (!firstPlay && turns == 2)) {
            int currX = event->x();
            int currY = event->y();
            qDebug() << currX << " " << currY << endl;

            if (currX < 45 || currX > 447 || currY < 45 || currY > 447) {
                qDebug() << "Not int the active area\n";
            } else {
                int tCol = abs(currX - 50 + 10) / 28;
                int tRow = abs(currY - 50 + 10) / 28;
                if (playMap[tRow][tCol] == 0) {
                    playMap[tRow][tCol] = turns;
                    countChess++;
                    currentPoint.setX(tRow);
                    currentPoint.setY(tCol);
                    changeTurn();
                    chessLise.push_back( currentPoint );


                    this->update();


                    for (int i = 0; i < winsWayCount; ++i) {
                            // 靠近胜利+1
                            if (winsArr[tRow][tCol][i]) {
                            playerWinsWayStatisticArr[i]++;
                            // i方法下电脑无法赢
                            computerWinsWayStatisticArr[i] = 10;
                            if (playerWinsWayStatisticArr[i] == 5) {
                                winShow();
                                break;
                            }
                        }
                    }

                    if (gameStart && countChess == 15 * 15) {
                        tie();
                    }

                    if (gameStart) getAI_next();

//                    if (checkWin()) {
//                        winShow();
//                    } else if (countChess == 15*15) {
//                        tie();
//                    }

                } else {
                    qDebug() << "there has had a Chess\n";
                }
            }
        }
    }
}


void Widget::tie() {
    QString str = "Tie";
    if (QMessageBox::question(this, str, "Again?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        init();
    } else {
        exitButClicked();
    }
}


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);

    QPen pen(Qt::black);
    painter->setPen(pen);
    //  纵横线
    for (int i = 0; i < 15; ++i) {
        painter->drawLine(50+i*28, 50, 50+i*28, 442);
    }
    for (int i = 0; i < 15; ++i) {
        painter->drawLine(50, 50+i*28, 442, 50+i*28);
    }


    QBrush bru(Qt::black);
    painter->setBrush(bru);


    // 中间的小圆 和四角小圆
    painter->drawEllipse(50 + 7*28 - 2.5, 50 + 7*28 - 2.5, 5, 5);
    painter->drawEllipse(50 + 3*28 - 2.5, 50 + 3*28 - 2.5, 5, 5);
    painter->drawEllipse(50 + 3*28 - 2.5, 50 + 11*28 - 2.5, 5, 5);
    painter->drawEllipse(50 + 11*28 - 2.5, 50 + 3*28 - 2.5, 5, 5);
    painter->drawEllipse(50 + 11*28 - 2.5, 50 + 11*28 - 2.5, 5, 5);

    // 画棋子
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            switch (playMap[i][j]) {
            case 1:
                bru.setColor(Qt::black), painter->setBrush(bru);
                painter->drawEllipse(50 + j*28 - 12.5, 50 + i*28 - 12.5, 25, 25);
                break;
            case 2:
                bru.setColor(Qt::white), painter->setBrush(bru);
                painter->drawEllipse(50 + j*28 - 12.5, 50 + i*28 - 12.5, 25, 25);
                break;
            default:
                break;
            }
        }
    }

    // 标志当前点
    QBrush t;
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->setBrush(t);


    if (gameStart)
    {
        painter->drawRect(50 + currentPoint.y() * 28 - 12.5, 50 + currentPoint.x() * 28 - 12.5, 25, 25);
    }
}
