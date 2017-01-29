#include "widget.h"


// AI核心


void Widget::statisticwinWays() {

    this->deep_think_computer_max.resize(this->thinkDeep*2+2);
    this->deep_think_player_max.resize(this->thinkDeep*2+2);
//    deep_think_computer_max.resize(thinkDeep * ２　+ 2);
//    deep_think_player_max.resize(thinkDeep *　２　＋ 2);

    winsWayCount = 0;

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            for (int k = 0; k < 600; ++k) {
                winsArr[i][j][k] = false;
            }
        }
    }

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
                            playerScore[i][j] += 5;
                            break;
                        case 2:
                            playerScore[i][j] += 50;
                            break;
                        case 3:
                            if (!live3(i, j, "p")) {
                                playerScore[i][j] += 100;
                            } else {
                                playerScore[i][j] += 1000;
                            }
                                break;
                        case 4:
                            playerScore[i][j] += 1000;
                            break;
                    }
                    switch (computerWinsWayStatisticArr[k]) {
                        case 1:
                            computerScore[i][j] += 5;
                            break;

                        case 2:
                            computerScore[i][j] += 50;
                            break;

                        case 3:
                        if (!live3(i, j, "c")) {
                            computerScore[i][j] += 100;
                        } else {


                            computerScore[i][j] += 1000;
                        }
                            break;

                        case 4:
                            computerScore[i][j] +=  1000;
                            break;

                    }
                }
            }
        }
    }

}


bool Widget::__live3__(int r, int c, int t) {
    int i, j;
    // 1.2.#*000*#
    //3 4 00*0#####
    // 5.0 0*0 0

    //1 *000
    // 行
    int count = 0;
    for (i = c + 1; i <= c+3 && i<15 && playMap[r][i] == t; ++i) {
        count++;
    }
    if (count == 3 && i<15 && playMap[r][i] == 0) {
//        qDebug() << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$1 row\n";
        return true;
    }
    // 列
    count = 0;
    for (i = r + 1; i <= r+3 && i <15 && playMap[i][c] == t; ++i) {
        count++;
    }
    if (count == 3 && i<15 && playMap[i][c] == 0) {
//        qDebug() << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$2 row\n";
        return true;
    }
    // 主对角线
    count = 0;
    for(i = r + 1, j = c + 1; i <= r+3 && i<15 && j <= c+3 && j<15 && playMap[i][j] == t; ++j, ++i) {
        count++;
    }
    if (count == 3 && i<15 && j<15 && playMap[i][j] == 0) {
        return true;
    }
    //福对角线
    count = 0;
    for(i = r + 1, j = c - 1; i <= r+3 && i < 15 && j >= c-3 && j>=0 && playMap[i][j] == t; --j, ++i) {
        count++;
    }
    if (count == 3 && i < 15 && j>= 0 && playMap[i][j] == 0) {
        return true;
    }
    // 2 000*
    // 行
    count = 0;
    for (i = c - 1; i >= c-3 && i>=0 && playMap[r][i] == t; --i) {
        count++;
    }
    if (count == 3 && i>=0 && playMap[r][i] == 0) {
        return true;
    }
    // 列
    count = 0;
    for (i = r - 1; i >= r-3 && i >=0 && playMap[i][c] == t; --i) {
        count++;
    }
    if (count == 3 && i>=0 && playMap[i][c] == 0) {
        return true;
    }
    // 主对角线
    count = 0;
    for(i = r - 1, j = c - 1; i >= r-3 && i>=0 && j >= c-3 && j>=0 && playMap[i][j] == t; --j, --i) {
        count++;
    }
    if (count == 3 && i>=0 && j>=0 && playMap[i][j] == 0) {
        return true;
    }
    //福对角线
    count = 0;
    for(i = r - 1, j = c + 1; i >= r-3 && i>=0 && j <= c+3 && j<15 && playMap[i][j] == t; ++j, --i) {
        count++;
    }
    if (count == 3 && i>=0 && j<15 && playMap[i][j] == 0) {
        return true;
    }
    //3 00*0#####
    // 行
    count = 0;
    for (i = c - 1; i >= c-2 && i>=0 && playMap[r][i] == t; --i) {
        count++;
    }
    if (c + 1 < 15 && playMap[r][c+1] == t) {
        count++;
    }
    if (count == 3 && i>=0 && playMap[r][i] == 0 && c+2 < 15 && playMap[r][c+2] == 0) {
        return true;
    }
    // 列
    count = 0;
    for (i = r - 1; i >= r-2 && i >=0 && playMap[i][c] == t; --i) {
        count++;
    }
    if (r + 1 < 15 && playMap[r+1][c] == t) {
        count++;
    }
    if (count == 3 && i>=0 && playMap[i][c] == 0 && r+2 < 15 && playMap[r+2][c] == 0) {
        return true;
    }
    // 主对角线
    count = 0;
    for(i = r - 1, j = c - 1; i >= r-2 && i>=0 && j >= c-2 && j>=0 && playMap[i][j] == t; --j, --i) {
        count++;
    }
    if (r + 1 < 15 && c + 1 < 15 && playMap[r+1][c+1] == t) {
        count++;
    }
    if (count == 3 && i>=0 && j>=0 && playMap[i][j] == 0 && r+2<15 && c+2<15 && playMap[r+2][c+2] == 0) {
        return true;
    }
    //福对角线
    count = 0;
    for(i = r - 1, j = c + 1; i >= r-2 && i>=0 && j <= c+2 && j<15 && playMap[i][j] == t; ++j, --i) {
        count++;
    }
    if (r + 1 < 15 && c - 1 >= 0 && playMap[r+1][c+1] == t) {
        count++;
    }
    if (count == 3 && i>=0 && j<15 && playMap[i][j] == 0 && r + 2 < 15 && c - 2 >= 0 && playMap[r+2][c-2] == 0) {
        return true;
    }

    //4 0*00#####
    // 行
    count = 0;
    for (i = c+1; i <= c+2 && i < 15 && playMap[r][i] == t; ++i) {
        count++;
    }
    if (c - 1 >= 0 && playMap[r][c-1] == t) {
        count++;
    }
    if (count == 3 && i<15 && playMap[r][i] == 0 && c-2 >= 0 && playMap[r][c-2] == 0) {
        return true;
    }
    // 列
    count = 0;
    for (i = r + 1; i <= r+2 && i<15 && playMap[i][c] == t; ++i) {
        count++;
    }
    if (r - 1 >= 0 && playMap[r-1][c] == t) {
        count++;
    }
    if (count == 3 && i<15 && playMap[i][c] == 0 && r - 2 >= 0 && playMap[r-2][c] == 0) {
        return true;
    }
    // 主对角线
    count = 0;
    for(i = r + 1, j = c + 1; i <= r+2 && i<15 && j <= c+2 && j<15 && playMap[i][j] == t; ++j, ++i) {
        count++;
    }

    if (r - 1 >= 0 && c - 1 >= 0 && playMap[r-1][c-1] == t) {
        count++;
    }
    if (count == 3 && i<15 && j<15 && playMap[i][j] == 0 && r-2>=0 && c-2>=0 && playMap[r-2][c-2] == 0) {
        return true;
    }
    //福对角线
    count = 0;
    for(i = r + 1, j = c - 1; i <= r+2 && i<15 && j >= c-2 && j>=0 && playMap[i][j] == t; ++j, --i) {
        count++;
    }
    if (r - 1 >= 0 && c + 1 < 15 && playMap[r-1][c+1] == t) {
        count++;
    }
    if (count == 3 && i<15 && j>=0 && playMap[i][j] == 0 && r - 2 >= 0 && c + 2 < 15 && playMap[r-2][c+2] == 0) {
        return true;
    }
    return false;
    // 5 0 0*0 0


}

bool Widget::live3(int r, int c, QString who) {
    if (who == "c") {
        if (firstPlay) {
            return __live3__(r,c,2);
        } else {
            return __live3__(r,c,1);
        }
    } else {
        if (firstPlay) {
            return __live3__(r,c,1);
        } else {
            return __live3__(r,c,2);
        }
    }
}

void Widget::getMaxScore() {
    int tx = 0;
    int ty = 0;
    int tMax = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (playMap[i][j] == 0 && tMax < playerScore[i][j]) {
                tx = i;
                ty = j;
                tMax = playerScore[i][j];
            }
        }
    }
    player_max.setX(tx);
    player_max.setY(ty);


    tx = ty = 0;
    tMax = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (playMap[i][j] == 0 && tMax < computerScore[i][j]) {
                tx = i;
                ty = j;
                tMax = computerScore[i][j];
            }
        }
    }
    AI_max.setX(tx);
    AI_max.setY(ty);
}

void Widget::deepThinkGetScore(int i) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (playMap[i][j] != 0) continue;
            for (int k = 0; k < winsWayCount; ++k) {
                if (winsArr[i][j][k]) {

                    switch (playerWinsWayStatisticArr[k]) {
                        case 1:
                            playerScore[i][j] += 250;
                            break;
                        case 2:
                            playerScore[i][j] += 800;
                            break;
                        case 3:
                            playerScore[i][j] += 4000;
                            break;
                        case 4:
                            playerScore[i][j] += 10000;
                            break;
                    }

                    switch (computerWinsWayStatisticArr[k]) {
                        case 1:
                            computerScore[i][j] += 200;
                            break;
                        case 2:
                            computerScore[i][j] += 700;
                            break;
                        case 3:
                            computerScore[i][j] += 3000;
                            break;
                        case 4:
                            computerScore[i][j] += 9000;
                            break;
                    }
                }
            }
        }
    }
}

void Widget::deepThinkGetMaxScore(int i) {
    int tx = 0;
    int ty = 0;
    int tMax = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (playMap[i][j] == 0 && tMax < playerScore[i][j]) {
                tx = i;
                ty = j;
                tMax = playerScore[i][j];
            }
        }
    }
//    player_max.setX(tx);
//    player_max.setY(ty);
    deep_think_player_max[i - 1].setX(tx);
    deep_think_player_max[i - 1].setY(ty);


    tx = ty = 0;
    tMax = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (playMap[i][j] == 0 && tMax < computerScore[i][j]) {
                tx = i;
                ty = j;
                tMax = computerScore[i][j];
            }
        }
    }
//    AI_max.setX(tx);
//    AI_max.setY(ty);
    deep_think_computer_max[i - 1].setX(tx);
    deep_think_computer_max[i - 1].setY(ty);

}

void Widget::twoDeepThink() {
}

void Widget::getAI_next()
{
    int tTurn = turns;
    changeTurn();

    // 评分
    getScore();

    // 最值筛选
    getMaxScore();


    // 先堵

    int tRow, tCol;

    // 玩家得分 就防守
    if ((double)playerScore[player_max.x()][player_max.y()] / (double)computerScore[AI_max.x()][AI_max.y()] > 0.95) {
        playMap[player_max.x()][player_max.y()] = tTurn;
        tRow = player_max.x();
        tCol = player_max.y();
    } else {
        playMap[AI_max.x()][AI_max.y()] = tTurn;
        tRow = AI_max.x();
        tCol = AI_max.y();
    }
    qDebug() << "##################" << endl;
    qDebug() << "AI next " << tRow << " " << tCol << endl;
    qDebug() << "##################" << endl;
    countChess++;
    currentPoint.setX(tRow);
    currentPoint.setY(tCol);
    chessLise.push_back( currentPoint );


    this->update();



    for (int i = 0; i < winsWayCount; ++i) {
        // 靠近胜利+1
        if (winsArr[tRow][tCol][i]) {
            computerWinsWayStatisticArr[i]++;
            // i方法下人类无法赢
            playerWinsWayStatisticArr[i] = 10;
            if (computerWinsWayStatisticArr[i] == 5) {
                winShow();
                break;
            }
        }
    }

    if (gameStart && countChess == 15 * 15) {
        tie();
    }



}
