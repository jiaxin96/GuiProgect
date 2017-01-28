#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QRect>
#include <QPen>
#include <QPalette>
#include <QList>
#include <QPoint>
#include <QMessageBox>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


public slots:
    void startFirstButClicked();
    void startLaterButClicked();
    void exitButClicked();
    void backOneButClicked();

private:

    // UI布局 按钮界面设计
    Ui::Widget *ui;
    QLabel *whichOneTurn;
    QLabel *whichOneTurnMess;
    QPushButton *startFirstBut;
    QPushButton *startLaterBut;
    QPushButton *exitBut;
    QPushButton *backOne;

//    QPushButton *playOrder;




    // 棋类数组
    int playMap[15][15];


    // 游戏开局 结束逻辑判断
    // 是否先手
    bool firstPlay;
    int turns;
    bool checkWin();
    void winShow();
    void changeTurn();
    void tie();
    void init();
    bool gameStart;
    bool canStart;
    int countChess;


    // 悔棋
    QList<QPoint> chessLise;

    // AI 部分
    // #####
    // #####
    QPoint AInext;
    QPoint currentPoint;

    // AI核心
    void getAI_next();


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H
