#pragma once
#include "StageInformation.h"

#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

class GlobalVariant {
private:
    int level;
    int ab_x, ab_y;	//화면중 블럭이 나타나는 좌표의 절대위치
    int block_shape, block_angle, block_x, block_y;
    int next_block_shape;
    int score;
    int lines;
    int ctr;
    int is_gameover; // The Boolean type check variable.
    void initTotalBlock();
    char total_block[21][14];		//화면에 표시되는 블럭들

public:
    GlobalVariant();
    StageInformation stage_data[10];
    void init(int level, int lines, int ab_x, int ab_y);
    int getLevel();
    int getAbsoluteX();
    int getAbsoluteY();
    int getCtr();
    int getNextBlockShape();
    int getBlockAngle();
    int getBlockX();
    int getBlockY();
    int getBlockShape();
    int getLine();
    int getScore();
    int getGameOver();

    // Ptr return - type.
    int* getPtrBlockAngle();
    int* getPtrBlockX();
    int* getPtrBlockY();
    int* getPtrBlockShape();
    int* getPtrNextBlockShape();

    // Array return - type
    char(*getTotalBlock())[14]{
        return this->total_block;
    }

    // Something to set.
    void setBlockShape(int blockShape);
    void setNextBlockShape(int nextBlock);
    void setBlockAngle(int blockangle);
    void setBlockX(int blox);
    void setCtr(int ct);
    void setLine(int ln);
    void setScore(int sc);
    void setLevel(int lvl);
    void setGameOver(int val);
    void setTotalBlock(int x, int y, int value) {
        this->total_block[y][x] = value;
    }
    void setTotalBlock(int x, int y, int value, bool isBitOrOperator) {
        this->total_block[y][x] |= value;
    }
};

enum {
    BLACK,      /*  0 : 까망 */
    DARK_BLUE,    /*  1 : 어두운 파랑 */
    DARK_GREEN,    /*  2 : 어두운 초록 */
    DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
    DARK_RED,    /*  4 : 어두운 빨강 */
    DARK_VOILET,  /*  5 : 어두운 보라 */
    DARK_YELLOW,  /*  6 : 어두운 노랑 */
    GRAY,      /*  7 : 회색 */
    DARK_GRAY,    /*  8 : 어두운 회색 */
    BLUE,      /*  9 : 파랑 */
    GREEN,      /* 10 : 초록 */
    SKY_BLUE,    /* 11 : 하늘 */
    RED,      /* 12 : 빨강 */
    VOILET,      /* 13 : 보라 */
    YELLOW,      /* 14 : 노랑 */
    WHITE,      /* 15 : 하양 */
};