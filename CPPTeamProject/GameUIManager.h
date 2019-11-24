#pragma once
#pragma warning(disable:4996)

#include "BlockManager.h"
#include "GlobalVariant.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>

#define FOURTH_MAT 7
#define THIRD_MAT 4
#define SECOND_MAT 10
#define FIRST_MAT 6

using namespace std;

class GameUIManager : public BlockManager {
private:
    GlobalVariant& gv;
public:
    GameUIManager(GlobalVariant& input);
    /**
     * Shows shape-angle from poconst int&.
     * shape: Could be random, but anyway, its shape of block.
     * angle: Could be random, but also, its rotation of block.
     * x/y: Could be random, absolute starting poconst int&.
     */
    int show_cur_block(const int& shape, const int& angle, const int& x, const int& y);

    //Erase current block information(More likely, override with spaces)
    int erase_cur_block(const int& shape, const int& angle, const int& x, const int& y);
    int show_total_block();

    /**
     * Show next block on Top-Right.
     * It basically make box and IN THAT BOX, they show next block.
     * Shape is previously created by make_new_block();
     */
    int show_next_block(const int& shape);

    int show_logo();
    int show_gamestat();

    int show_gameover();

    int input_data();
    void SetColor(const int& color);
    int gotoxy(const int& x, const int& y);
};

