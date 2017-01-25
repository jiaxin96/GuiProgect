#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QPoint>
#include <QPushButton>
#include <QMessageBox>
#include <QLayout>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QLabel>
#include <QFont>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:


    void upGoingSingal();
    void downGoingSingal();
    void leftGoingSingal();
    void rightGoingSingal();

public slots:
    void upGoingSolt();
    void downGoingSolt();
    void leftGoingSolt();
    void rightGoingSolt();
    void exitButSolt();
    void startButSolt();
    void timeIntervalOffAction();
private:
    void  init();
    void snakeDie();
    bool conflictWithSnake(int x, int y);
    bool conflictWithSelf(int x, int y);
    bool conflictWithWall(int x, int y);
    enum DIRECTION {LL, RR, UU, DD};


    QPoint food;

    QTimer *timer;

    int score;
    // 蛇的属性
    QList<QPoint> snakeBody;
    DIRECTION headDir = DIRECTION::RR;


    // 地图基本属性
    int const MASH_ROW = 30;
    int const MASH_COLUMN = 30;
    int const MASH_W = 20;

    int head_x = MASH_COLUMN / 2;
    int head_y = MASH_ROW / 2;

    void generateOneFood();

    // 布局
    QLabel *scoreMess;
    QLabel *scoreCount;

    QPushButton *beginBnt;
    QPushButton *exitBnt;

//    bool conflict(int x, int y);

    // QWidget interface
protected:
//    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
