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
    gv.stage_data[0].init(40, 20, 20);
    gv.stage_data[1].init(38, 18, 20);
    gv.stage_data[2].init(35, 18, 20);
    gv.stage_data[3].init(30, 17, 20);
    gv.stage_data[4].init(25, 16, 20);
    gv.stage_data[5].init(20, 14, 20);
    gv.stage_data[6].init(15, 14, 20);
    gv.stage_data[7].init(10, 13, 20);
    gv.stage_data[8].init(6, 12, 20);
    gv.stage_data[9].init(4, 11, 99999);
    return 0;
}

int TetrisCore::make_new_block() {
    int shape;
    int i;
    i = rand() % 100;
    if (i <= gv.stage_data[gv.getLevel()].getStickRate())		//����� ����Ȯ�� ���
        return 0;							//����� ������� ����

    shape = (rand() % 6) + 1;		//shape���� 1~6�� ���� ��
    return shape;
}

//Check wheter block is touching elswhere.
//Returns 1 if they are touching anything, 0 when not.
// INNER FUNCTION
int TetrisCore::strike_check(int shape, int angle, int* x, int y, int isRot) {
    int i, j;
    int block_dat;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (((*x + j) == 0) || ((*x + j) == 13))
                block_dat = 1;
            else {
                if ((y + i) < 0) continue;
                block_dat = gv.total_block[y + i][*x + j];
            }
            if ((block_dat == 1) && (gui.getBlock()[shape][angle][i][j] == 1)) {
                if (isRot) {
                    if ((*x + j) == 13) {
                        (*x)--;
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
            if (gv.total_block[i][j] == 0)
                break;
        }
        if (j == 13) { //������ �� ä������
            gv.setLine((gv.getLine() + 1));
            gui.show_total_block();
            SystemUIManager::SetColor(BLUE);
            SystemUIManager::gotoxy(1 * 2 + gv.getAbsoluteX(), i + gv.getAbsoluteY());
            for (j = 1; j < 13; j++) {
                cout << "��";
                Sleep(10);
            }
            SystemUIManager::gotoxy(1 * 2 + gv.getAbsoluteX(), i + gv.getAbsoluteY());
            for (j = 1; j < 13; j++) {
                cout << "  ";
                Sleep(10);
            }

            for (k = i; k > 0; k--) {
                for (j = 1; j < 13; j++)
                    gv.total_block[k][j] = gv.total_block[k - 1][j];
            }
            for (j = 1; j < 13; j++)
                gv.total_block[0][j] = 0;
            gv.setScore(gv.getScore() + 100 + (gv.getLevel() * 10) + (rand() % 10));
            if (gv.stage_data[gv.getLevel()].getClearLine() <= gv.getLine()) { //Ŭ���� ��������
                gv.setLevel(gv.getLevel() + 1);
                gv.setLine(0);
            }
            gui.show_gamestat();
        }
    }
    return 0;
}

// INNER FUNCTION
int TetrisCore::merge_block(int shape, int angle, int x, int y) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            gv.total_block[y + i][x + j] |= gui.getBlock()[shape][angle][i][j];
        }
    }
    check_full_line();
    gui.show_total_block();

    return 0;
}

// Set initial state for first-block start.
int TetrisCore::block_start(int* angle, int* x, int* y) {
    *x = 5;
    *y = -3;
    *angle = 0;
    return 0;
}

int TetrisCore::move_block(int* shape, int* angle, int* x, int* y, int* next_shape) {
    gui.erase_cur_block(*shape, *angle, *x, *y);

    (*y)++;	//������ ��ĭ �Ʒ��� ����
    if (strike_check(*shape, *angle, x, *y, 0) == 1) {
        (*y)--;
        if (*y < 0)	//���ӿ���
        {
            return 1;
        }
        merge_block(*shape, *angle, *x, *y);
        *shape = *next_shape;
        *next_shape = make_new_block();

        block_start(angle, x, y);	//angle,x,y�� ��������
        gui.show_next_block(*next_shape);
        return 2;
    }
    return 0;
}