#include "game2048.h"
#include <cstdlib>
#include <ctime>

Game2048::Game2048() {
    srand(static_cast<unsigned int>(std::time(nullptr)));
    initialize();
}//以系统时间作为随机数种子

void Game2048::initialize() {
    // 初始化游戏面板
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
    addRandomTile();
    addRandomTile();
}

bool Game2048::CheckFull(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(board[i][j] == 0) return false;
        }
    }
    return true;
}

bool Game2048::manipulate(int direction) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            PreBoard[i][j]=board[i][j];
        }
    }
    prepoint=point;
    Revisible=1;
    if(!judge()) return true;
    point--;
    step++;
    switch (direction) {
    case 1: // 向左
        moveLeft();
        if(!moveLeft()) return false;
        break;
    case 2: // 向右
        moveRight();
        if(!moveRight()) return false;
        break;
    case 3: // 向上
        moveUp();
        if(!moveUp()) return false;
        break;
    case 4: // 向下
        moveDown();
        if(!moveDown()) return false;
        break;
    }
    addRandomTile(); // 每次操作后添加新方块
    return true;
}

bool Game2048::judge(){
    //右侧判断
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == board[i][j + 1]) return true;
        }
    }
    //下侧判断
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4 ; j++) {
            if (board[i][j] == board[i+1][j]) return true;
        }
    }
    //空位判断
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0)
                return true;
        }
    }
    return false;
}

int Game2048::getTile(int x, int y) const {
    return board[x][y];
}

int Game2048::ranNum() {
    return (rand() % 2 + 1) * 2;
}

int Game2048::ranNum1() {
    return rand() % 4;
}

void Game2048::addRandomTile() {
    int x, y;
    do {
        x = ranNum1();
        y = ranNum1();
    } while (board[x][y] != 0);

    board[x][y] = ranNum();
}

bool Game2048::moveLeft() {
    int status=0;
    if(CheckFull()){
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j > 0; j--) {
                if (board[i][j] == board[i][j - 1]) status=1;
            }
        }
        if(status==0) return false;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >0; j--) {
            if (board[i][j] == board[i][j - 1]) {
                board[i][j - 1] *= 2;
                point+=board[i][j];
                board[i][j] = 0;
            }
            if (board[i][j] != 0 && board[i][j - 1] == 0) {
                board[i][j - 1] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >0; j--) {
            if (board[i][j] != 0 && board[i][j - 1] == 0) {
                board[i][j - 1] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
    return true;
}

bool Game2048::moveRight() {
    int status=0;
    if(CheckFull()){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == board[i][j + 1]) status=1;
            }
        }
        if(status==0) return false;
    }

        for (int i = 0;  i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == board[i][j + 1]) {
                        board[i][j + 1] *= 2;
                        point+=board[i][j];
                        board[i][j] = 0;
                    }
                    if (board[i][j] != 0 && board[i][j + 1] == 0) {
                        board[i][j+1] = board[i][j];
                        board[i][j]= 0;
                    }
                }
        }
        for (int i = 0;  i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] != 0 && board[i][j + 1] == 0) {
                        board[i][j+1] = board[i][j];
                        board[i][j]= 0;
                    }
                }
        }
        return true;
}

bool Game2048::moveUp() {
    int status=0;
    if(CheckFull()){
                for (int i = 3; i >0; i--) {
                    for (int j = 0; j < 4; j++) {
                        if (board[i][j] == board[i-1][j]) status=1;
                    }
                }
                if(status==0) return false;
        }
    for (int i = 3; i>0; i--) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == board[i-1][j]) {
                board[i-1][j] *= 2;
                point+=board[i][j];
                board[i][j] = 0;
            }
            if (board[i][j] != 0 && board[i - 1][j] == 0) {
                board[i-1][j] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
    for (int i = 3; i>0; i--) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0 && board[i - 1][j] == 0) {
                board[i-1][j] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
    return true;
}

bool Game2048::moveDown() {
    int status=0;
    if(CheckFull()){
        for (int i = 0; i <3; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == board[i+1][j]) status=1;
            }
        }
        if(status==0) return false;
    }
    for (int i = 0; i <3; i++) {
        for (int j = 0; j <4; j++) {
            if (board[i][j] == board[i+1][j]) {
                board[i+1][j] *= 2;
                point+=board[i][j];
                board[i][j] = 0;
            }
            if (board[i][j] != 0 && board[i + 1][j] == 0) {
                board[i+1][j] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
    for (int i = 0; i <3; i++) {
        for (int j = 0; j <4; j++) {
            if (board[i][j] != 0 && board[i + 1][j] == 0) {
                board[i+1][j] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
    return true;
}

bool Game2048::Revise(){
    if(!Revisible) return false;
    if(Revisible){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j]=PreBoard[i][j];
        }
    }
    step--;
    point=prepoint;
    Revisible=0;
    }
    return true;
}