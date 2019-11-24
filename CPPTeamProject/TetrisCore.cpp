#include "TetrisCore.h"

TetrisCore::TetrisCore(GameUIManager& gameUI, GlobalVariant& glovalVar) : gui(gameUI), gv(glovalVar) {
}

/**
 * The Questions.
 * 1. Why init should return 0? Seems like nothing is taking return value of init.
 */
int TetrisCore::init() {

    gv.init(0, 0, 5, 1);
    gv.setGameOver(0);

    // Initiate stage level data.
    gv.callInitStage(0, 40, 20, 20);
    gv.callInitStage(1, 38, 18, 20);
    gv.callInitStage(2, 35, 18, 20);
    gv.callInitStage(3, 30, 17, 20);
    gv.callInitStage(4, 25, 16, 20);
    gv.callInitStage(5, 20, 14, 20);
    gv.callInitStage(6, 15, 14, 20);
    gv.callInitStage(7, 10, 13, 20);
    gv.callInitStage(8, 6, 12, 20);
    gv.callInitStage(9, 4, 11, 99999);
    return 0;
}

int TetrisCore::make_new_block() {
    int shape;
    int i;
    i = rand() % 100;
    if (i <= gv.getStageInformation()[gv.getLevel()].getStickRate())		//막대기 나올확률 계산
        return 0;							//막대기 모양으로 리턴

    shape = (rand() % 6) + 1;		//shape에는 1~6의 값이 들어감
    return shape;
}

//Check wheter block is touching elswhere.
//Returns 1 if they are touching anything, 0 when not.
// INNER FUNCTION
int TetrisCore::strike_check(const int& shape, const int& angle, int& x, const int& y, const int& isRot) {
    int i, j;
    int block_dat;

    for (i = 0; i < SECOND_MAT; i++) {
        for (j = 0; j < FIRST_MAT; j++) {
            if (((x + j) == 0) || ((x + j) == 13))
                block_dat = 1;
            else {
                if ((y + i) < 0) continue;
                block_dat = gv.getTotalBlock()[y + i][x + j];
            }
            if ((block_dat == 1) && (gui.getBlock()[shape][angle][i][j] == 1)) {
                if (isRot) {
                    if ((x + j) == 13) {
                        (x)--;
                        gv.setCtr((gv.getCtr() + 1));
                        continue;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

// INNER FUNCTION
int TetrisCore::check_full_line() {
    int i, j, k;
    for (i = 0; i < 20; i++) {
        for (j = 1; j < 13; j++) {
            if (gv.getTotalBlock()[i][j] == 0)
                break;
        }
        if (j == 13) { //한줄이 다 채워졌음
            gv.setLine((gv.getLine() + 1));
            gui.show_total_block();
            gui.SetColor(BLUE);
            gui.gotoxy(1 * 2 + gv.getAbsoluteX(), i + gv.getAbsoluteY());
            for (j = 1; j < 13; j++) {
                cout << "□";
                Sleep(10);
            }
            gui.gotoxy(1 * 2 + gv.getAbsoluteX(), i + gv.getAbsoluteY());
            for (j = 1; j < 13; j++) {
                cout << "  ";
                Sleep(10);
            }

            for (k = i; k > 0; k--) {
                for (j = 1; j < 13; j++)
                    gv.setTotalBlock(j, k, gv.getTotalBlock()[k - 1][j]);
            }
            for (j = 1; j < 13; j++)
                gv.setTotalBlock(j, 0, 0);
            gv.setScore(gv.getScore() + 100 + (gv.getLevel() * 10) + (rand() % 10));
            if (gv.getStageInformation()[gv.getLevel()].getClearLine() <= gv.getLine()) { //클리어 스테이지
                gv.setLevel(gv.getLevel() + 1);
                gv.setLine(0);
            }
            gui.show_gamestat();
        }
    }
    return 0;
}

// INNER FUNCTION
int TetrisCore::merge_block(const int& shape, const int& angle, const int& x, const int& y) {
    int i, j;
    for (i = 0; i < SECOND_MAT; i++) {
        for (j = 0; j < FIRST_MAT; j++) {
            gv.setTotalBlock(x + j, y + i, gui.getBlock()[shape][angle][i][j], true);
        }
    }
    check_full_line();
    gui.show_total_block();

    return 0;
}

// Set initial state for first-block start.
int TetrisCore::block_start(int& angle, int& x, int& y) {
    x = 5;
    y = -3;
    angle = 0;
    return 0;
}

int TetrisCore::move_block(int& shape, int& angle, int& x, int& y, int& next_shape) {
    gui.erase_cur_block(shape, angle, x, y);

    (y)++;	//블럭을 한칸 아래로 내림
    if (strike_check(shape, angle, x, y, 0) == 1) {
        (y)--;
        if (y < 0)	//게임오버
        {
            return 1;
        }
        merge_block(shape, angle, x, y);
        shape = next_shape;
        next_shape = make_new_block();

        block_start(angle, x, y);	//angle,x,y는 포인터임
        gui.show_next_block(next_shape);
        return 2;
    }
    return 0;
}