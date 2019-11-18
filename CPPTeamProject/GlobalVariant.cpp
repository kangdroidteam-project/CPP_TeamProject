#include "GlobalVariant.h"

void GlobalVariant::initTotalBlock() {
/**
 * So, This iteration does:
 * 1. Every i, for j = 0, j = 13, set its var to 1.
 */
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            if ((j == 0) || (j == 13)) {
                total_block[i][j] = 1;
            } else {
                total_block[i][j] = 0;
            }
        }
    }

    for (int j = 0; j < 14; j++)			//화면의 제일 밑의 줄은 1로 채운다.
        total_block[20][j] = 1;
    // Afterall, those Iteration could minimize(or combine)
    // And those two for-operation does make some kind of beaker-shape array.
}

GlobalVariant::GlobalVariant() {
}

int GlobalVariant::getLevel() {
    return this->level;
}

int GlobalVariant::getAbsoluteX() {
    return this->ab_x;
}

int GlobalVariant::getAbsoluteY() {
    return this->ab_y;
}

int GlobalVariant::getCtr() {
    return this->ctr;
}

int GlobalVariant::getNextBlockShape() {
    return this->next_block_shape;
}

int GlobalVariant::getBlockAngle() {
    return this->block_angle;
}

int GlobalVariant::getBlockX() {
    return this->block_x;
}

int GlobalVariant::getBlockY() {
    return this->block_y;
}

int GlobalVariant::getBlockShape() {
    return this->block_shape;
}

int GlobalVariant::getLine() {
    return this->lines;
}

int GlobalVariant::getScore() {
    return this->score;
}

int GlobalVariant::getGameOver() {
    return this->is_gameover;
}

int* GlobalVariant::getPtrBlockAngle() {
    return &(this->block_angle);
}

int* GlobalVariant::getPtrBlockX() {
    return &(this->block_x);
}

int* GlobalVariant::getPtrBlockY() {
    return &(this->block_y);
}

int* GlobalVariant::getPtrBlockShape() {
    return &(this->block_shape);
}

int* GlobalVariant::getPtrNextBlockShape() {
    return &(this->next_block_shape);
}

char(*GlobalVariant::getTotalBlock())[14] {
    return this->total_block;
}

StageInformation(*GlobalVariant::getStageInformation()) {
    return this->stage_data;
}

void GlobalVariant::setBlockShape(int blockShape) {
    this->block_shape = blockShape;
}

void GlobalVariant::setNextBlockShape(int nextBlock) {
    this->next_block_shape = nextBlock;
}

void GlobalVariant::setBlockAngle(int blockangle) {
    this->block_angle = blockangle;
}

void GlobalVariant::setBlockX(int blox) {
    this->block_x = blox;
}

void GlobalVariant::setCtr(int ct) {
    this->ctr = ct;
}

void GlobalVariant::setLine(int ln) {
    this->lines = ln;
}

void GlobalVariant::setScore(int sc) {
    this->score = sc;
}

void GlobalVariant::setLevel(int lvl) {
    this->level = lvl;
}

void GlobalVariant::setGameOver(int val) {
    this->is_gameover = val;
}

void GlobalVariant::setTotalBlock(int x, int y, int value) {
    this->total_block[y][x] = value;
}

void GlobalVariant::setTotalBlock(int x, int y, int value, bool isBitOrOperator) {
    this->total_block[y][x] |= value;
}

void GlobalVariant::callInitStage(int index, int speed, int stick_rate, int clear_line) {
    this->stage_data[index].init(speed, stick_rate, clear_line);
}

void GlobalVariant::init(int level, int lines, int ab_x, int ab_y) {
    this->level = level;
    this->lines = lines;
    this->ab_x = ab_x;
    this->ab_y = ab_y;

    this->block_shape = 0;
    this->block_angle = 0;
    this->block_x = 0;
    this->block_y = 0;
    this->next_block_shape = 0;
    this->score = 0;
    this->ctr = 0;
    initTotalBlock();
}
