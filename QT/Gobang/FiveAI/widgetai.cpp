#include "widget.h"


// AI核心


void Widget::statisticwinWays() {

    winsWayCount = 0;


    //  横向数组

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 11; ++j) {
            for (int k = 0; k < 5; ++k) {
                winsArr[i][j + k][winsWayCount] = true;
            }
            winsWayCount++;
        }
    }

    //  纵向
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 11; ++j) {
            for (int k = 0; k < 5; ++k) {
                winsArr[j + k][i][winsWayCount] = true;
            }
            winsWayCount++;
        }
    }

    //  主对角线方向
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            for (int k = 0; k < 5; ++k) {
                winsArr[i + k][j + k][winsWayCount] = true;
            }
            winsWayCount++;
        }
    }


    // 副对角线方向
    for (int i = 0; i < 11; ++i) {
        for (int j = 14; j > 3; --j) {
            for (int k = 0; k < 5; ++k) {
                winsArr[i + k][j - k][winsWayCount] = true;
            }
            winsWayCount++;
        }
    }

    qDebug() << "Win Ways number is " << winsWayCount << endl;

}


void Widget::initScore() {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            playerScore[15][15] = 0;
            computerScore[15][15] = 0;
        }
    }
}

void Widget::getScore() {

    initScore();

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (playMap[i][j] != 0) continue;
            for (int k = 0; k < winsWayCount; ++k) {
                if (winsArr[i][j][k]) {
                    switch (playerWinsWayStatisticArr[k]) {
                        case 1:
                            playerScore[i][j] += 10;
                            break;
                        case 2:
                            playerScore[i][j] += 50;
                            break;
                        case 3:
                            playerScore[i][j] += 1000;
                            break;
                        case 4:
                            playerScore[i][j] += 10000;
                            break;
                    }
                    switch (computerWinsWayStatisticArr[k]) {
                        case 1:
                            computerScore[i][j] += 30;
                            break;
                        case 2:
                            computerScore[i][j] += 100;
                            break;
                        case 3:
                            computerScore[i][j] += 1000;
                            break;
                        case 4:
                            computerScore[i][j] += 10000;
                            break;
                    }
                }
            }
        }
    }

}


void Widget::getMaxScore() {
    int tx = 0;
    int ty = 0;
    int tMax = playerScore[0][0];
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (tMax < playerScore[i][j]) {
                tx = i;
                ty = j;
                tMax = playerScore[i][j];
            }
        }
    }
    player_max.setX(tx);
    player_max.setY(ty);


    tx = ty = 0;
    tMax = computerScore[0][0];
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (tMax > computerScore[i][j]) {
                tx = i;
                ty = j;
            }
        }
    }
    AI_max.setX(tx);
    AI_max.setY(ty);
}

void Widget::getAI_next()
{

    // 评分
    getScore();

    // 最值筛选
    getMaxScore();


    // 先堵

    int tRow, tCol;

    // 玩家得分 就防守
    if (playerScore[player_max.x()][player_max.y()] >= computerScore[AI_max.x()][AI_max.y()]) {
        playMap[player_max.x()][player_max.y()] = turns;
        tRow = player_max.x();
        tCol = player_max.y();
    } else {
        playMap[AI_max.x()][AI_max.y()] = turns;
        tRow = AI_max.x();
        tCol = AI_max.y();
    }

    countChess++;
    currentPoint.setX(tRow);
    currentPoint.setY(tCol);
    chessLise.push_back( currentPoint );

    changeTurn();
    this->update();



    for (int i = 0; i < winsWayCount; ++i) {
        // 靠近胜利+1
        if (winsArr[tRow][tCol][i]) computerWinsWayStatisticArr[i]++;
        // i方法下人类无法赢
        playerWinsWayStatisticArr[i] = 10;
        if (computerWinsWayStatisticArr[i] == 5) {
            winShow();
            break;
        }
    }

    if (gameStart && countChess == 15 * 15) {
        tie();
    }



}
