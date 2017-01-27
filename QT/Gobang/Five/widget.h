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
    void startButClicked();
    void exitButClicked();

private:
    Ui::Widget *ui;
    QLabel *whichOneTurn;
    QLabel *whichOneTurnMess;
    QPushButton *startBut;
    QPushButton *exitBut;


    bool gameStart;

    int playMap[15][15];
    int turns;

    QPoint AInext;

    QPoint currentPoint;

    QPoint getAI_next();

    bool checkWin();
    void winShow();
    void init();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H
