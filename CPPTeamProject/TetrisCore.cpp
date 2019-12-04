#include "TetrisCore.h"

static int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };


TetrisCore::TetrisCore(GameUIManager& gameUI, GlobalVariant& glovalVar, BlockManager& blockman) : gui(gameUI), gv(glovalVar), bm(blockman) {

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

int TetrisCore::make_new_block(const int& level) {
    int shape,i;
    i = rand() % 100;
    if (i <= gv.getStageInformation()[gv.getLevel()].getStickRate()) {  //막대기 나올확률 계산
        shape = 0;						//막대기 모양으로 리턴
    }
    else shape = (rand() % 6)+1;		//shape에는 1~6의 값이 들어감
    if(level==1)
        bm.setColor(shape, gv.getBlockAngle());
    return shape;
}

int TetrisCore::strike_check(const int& level, const int& shape, const int& angle, int& x, const int& y, const int& isRot) {
    int i, j;
    int block_dat;
    int lx, ly;
    gv.getlevelXY(level, lx, ly);

    for (i = 0; i < lx; i++) {
        for (j = 0; j < ly; j++) {

            bool flag = true;
            if (((x + j) == 0) || ((x + j) == 13))
                block_dat = 1;
            else {
                if ((y + i) < 0) continue;
                block_dat = gv.getTotalBlock()[y + i][x + j];
            }

            switch (level) {
            case 0:
                if(bm.getFirstBlock()[shape][angle][i][j] == 0) {
                    flag = false;
                }
                break;
            case 1:
            case 3:
            case 5:
                if (bm.getBlock()[shape][angle][i][j] == 0) {
                    flag = false;
                }
                break;
            case 2:
                if (bm.getSecondBlock()[shape][angle][i][j] == 0) {
                    flag = false;
                }
                break;
            case 4:
                if (bm.getThirdBlock()[shape][angle][i][j] == 0) {
                    flag = false;
                }
                break;
            }
            if (!flag)continue;

            if ((block_dat !=0)) {
                if (isRot) {
                    if ((x + j) == 13) {
                        (x)--;
                        gv.setCtr((gv.getCtr() + 1));
                        continue;
                    }
                    else if((x+j)<0){
                        while ((x + j) > 0) {
                            (x)++;
                        }
                        gv.setCtr((gv.getCtr()) + 1);
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
            gui.show_total_block(0);
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

int TetrisCore::check_color(int x, int y, int& count, int k)
{
    while (k < 4) {

        gv.setColorBlock(x, y, 10);

        int x1 = x + dir[k][0];
        int y1 = y + dir[k][1];

        if ((x1 > 0 && x1 < 20) && (y1>0 && y1 < 13)) {
            if (gv.getTotalBlock()[x1][y1] == gv.getTotalBlock()[x][y] && gv.getTotalBlock()[x][y]!=0 && gv.getColorBlock()[x1][y1]!=10) {
                k++;
                count++;
                gv.setColorBlock(x1,y1, 10);
                check_color(x1, y1, count, 0);
                if (count > 2) {
                    gv.setjew(gv.getTotalBlock()[x][y]);
                }
            }
            else k++;
        }
        else k++;
        
    }
    return 0;
}

// INNER FUNCTION
int TetrisCore::merge_block(const int& level, int& shape,  int& angle,   int& x,   int& y) {
    int i, j;
    int lx, ly;
    
    gv.getlevelXY(level, lx, ly);

    switch (level) {
    case 0:
        for (i = 0; i < lx; i++) {
            for (j = 0; j < ly; j++) {
                gv.setTotalBlock(x + j, y + i, bm.getFirstBlock()[shape][angle][i][j], true);
            }
        }
        break;
    case 1:
    case 3:
    case 5:
        for (i = 0; i < lx; i++) {
            for (j = 0; j < ly; j++) {
                gv.setTotalBlock(x + j, y + i, bm.getBlock()[shape][angle][i][j], true);
            }
        }
        break;
    case 2:
        for (i = 0; i < lx; i++) {
            for (j = 0; j < ly; j++) {
                gv.setTotalBlock(x + j, y + i, bm.getSecondBlock()[shape][angle][i][j], true);
            }
        }
        break;
    case 4:
        for (i = 0; i < lx; i++) {
            for (j = 0; j < ly; j++) {
                gv.setTotalBlock(x + j, y + i, bm.getThirdBlock()[shape][angle][i][j], true);
            }
        }
        break;
    }



    check_full_line();

    if(level==1)
        colorpop();
    
    gui.show_total_block(level);
    return 0;
}

void TetrisCore::colorpop() {

    int count = 0;
    int k = 0, l;

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 24; j++) {
            count = 0;
            if (gv.getTotalBlock()[i][j] != 0)
                check_color(i, j, count, k);
            if (count > 2) {
                for (int k = 0; k < 21; k++) {
                    for (int p = 1; p < 14; p++) {
                        if (gv.getColorBlock()[k][p] == 10) {
                            gv.setTotalBlock(p, k, 0);
                        }
                    }
                }

                for (int k = 0; k < 21; k++) {
                    for (int p = 1; p < 14; p++) {
                        gv.setColorBlock(k, p, 0);
                        if (gv.getTotalBlock()[k][p] == 0 && gv.getTotalBlock()[k - 1][p] != 0) {
                            for (l = k; l > 0; l--) {
                                gv.setTotalBlock(p, l, gv.getTotalBlock()[l - 1][p]);
                            }
                            gv.setTotalBlock(p, 0, 0);
                        }
                    }
                }
                colorpop();
            }
            else {
                int cnt = 0;
                for (int i = 0; i < 21; i++) {
                    for (int j = 1; j < 14; j++) {
                        gv.setColorBlock(i, j, 0);
                    }
                }
            }

        }
    }
}


// Set initial state for first-block start.
int TetrisCore::block_start(const int& level, int& angle, int& x, int& y) {

    if (level == 2 || level == 4) x = 3;
    else x = 5;
    y = -3;
    angle = 0;
    return 0;
}

int TetrisCore::move_block(const int& level,int& shape, int& angle, int& x, int& y, int& next_shape) {
    gui.erase_cur_block(level,shape, angle, x, y);

    (y)++;	//블럭을 한칸 아래로 내림
    if (strike_check(level,shape, angle, x, y, 0) == 1) {
        (y)--;
        if (y < 0)	//게임오버
        {
            return 1;
        }

        merge_block(level,shape, angle, x, y);
        shape = next_shape;
        next_shape = make_new_block(level);
        
        
        if (level == 1) {
            gui.SetColor(WHITE);
            for (int i = 0; i < 5; i++) {
                cout << gv.getjew()[i] << " ";
            }
        }
        

        block_start(level,angle, x, y);	//angle,x,y는 포인터임
        gui.show_next_block(level,next_shape);

        return 2;
    }
    return 0;
}