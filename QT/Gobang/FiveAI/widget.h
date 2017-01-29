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
#include <stdlib.h>
#include <unistd.h>
#include <QVector>
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

    // 从1开始计数
    // 实际赢法数组从0开始计数

    // 通过statisticWinWays计算得到
    int winsWayCount;

    QPoint AInext;
    QPoint AI_max;
    QPoint player_max;

    QPoint currentPoint;

    // AI核心
    void getAI_next();
    void statisticwinWays();
    void getScore();
    void initScore();
    void getMaxScore();


    // 统计数组
    int playerWinsWayStatisticArr[600];
    int computerWinsWayStatisticArr[600];

    // 评分数组
    int playerScore[15][15];
    int computerScore[15][15];
    // 赢法数组
    bool winsArr[15][15][600];
    //  加强思考
    bool live3(int r, int c, QString who);
    bool __live3__(int r, int c, int t);

    int thinkDeep = 2;
    void deepThinkGetScore(int i);
    void deepThinkGetMaxScore(int i);
    void twoDeepThink();
    QVector< QPoint > deep_think_player_max;
    QVector< QPoint > deep_think_computer_max;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H
