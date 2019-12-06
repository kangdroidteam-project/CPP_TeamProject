#include "GameUIManager.h"
#include "GlobalVariant.h"
#include "BlockManager.h"

GameUIManager::GameUIManager(GlobalVariant& input, BlockManager& block) : gv(input),bm(block){
}
int GameUIManager::show_cur_block(const int& level, const int& shape, const int& angle, const int& x, const int& y, const bool& isFake) {
    int i, j; // The iteration variable. - Could be localized.

    int levelx;
    int levely; 

    gv.getlevelXY(level, levelx, levely);

    // Set Color based on block shape.
    switch (shape) {
    case 0: case 7:
        this->SetColor(RED);
        break;
    case 1: case 8:
        this->SetColor(BLUE);
        break;
    case 2: case 9:
        this->SetColor(SKY_BLUE);
        break;
    case 3: case 10:
        this->SetColor(WHITE);
        break;
    case 4: case 11:
        this->SetColor(YELLOW);
        break;
    case 5: case 12:
        this->SetColor(VOILET);
        break;
    case 6: case 13:
        this->SetColor(GREEN);
        break;
    }

    if (isFake) this->SetColor(DARK_GRAY);

    switch (level) {
    case 0:
        for (i = 0; i < levelx; i++) {
            for (j = 0; j < levely; j++) {

                if ((j + y) < 0) // Absolute starting point of y + j < 0
                    continue;

                if (bm.getFirstBlock()[shape][angle][j][i] != 0) {
                    this->gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                    cout << "■";
                }
            }
        }
        break;
    case 1:
        for (i = 0; i < levelx; i++) {
            for (j = 0; j < levely; j++) {

                if ((j + y) < 0) // Absolute starting point of y + j < 0
                    continue;

                if (bm.getBlock()[shape][angle][j][i] != 0) {
                    this->gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                    this->SetColor((int)(bm.getBlock()[shape][angle][j][i]));
                    if (isFake) this->SetColor(DARK_GRAY);
                    cout << "■";
                }
            }
        }
        break;
    case 3:
    case 5:
        for (i = 0; i < levelx; i++) {
            for (j = 0; j < levely; j++) {

                if ((j + y) < 0) // Absolute starting point of y + j < 0
                    continue;

                if (bm.getBlock()[shape][angle][j][i] != 0) {
                    this->gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                    cout << "■";
                }
            }
        }
        break;
    case 2: case 4:
        for (i = 0; i < levelx; i++) {
            for (j = 0; j < levely; j++) {

                if ((j + y) < 0) // Absolute starting point of y + j < 0
                    continue;

                if (bm.getSecondBlock()[shape][angle][j][i] != 0) {
                    this->gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                    cout << "■";
                }
            }
        }
        break;
    }

    this->SetColor(BLACK);
    this->gotoxy(77, 23);
    return 0;
}

//Erase current block information(More likely, override with spaces)
int GameUIManager::erase_cur_block(const int& level, const int& shape, const int& angle, const int& x, const int& y, const bool& isFake) {
    int i, j;
    int lx, ly;
    gv.getlevelXY(level, lx, ly);

    switch (level) {
    case 0:
        for (i = 0; i < lx; i++) {
            for (j = 0; j < ly; j++) {
                if (bm.getFirstBlock()[shape][angle][j][i] != 0) {
                    this->gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                    cout << "  ";
                    //break;

                }
            }
        }
        break;
    case 1:
    case 3:
    case 5:
        for (i = 0; i < lx; i++) {
            for (j = 0; j < ly; j++) {
                if (bm.getBlock()[shape][angle][j][i] != 0) {
                    this->gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                    cout << "  ";
                    //break;
                }
            }
        }
        break;
    case 2:case 4:
        for (i = 0; i < lx; i++) {
            for (j = 0; j < ly; j++) {
                if (bm.getSecondBlock()[shape][angle][j][i] != 0) {
                    this->gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                    cout << "  ";
                    //break;

                }
            }
        }
        break;
    }

    if (isFake) {
        int highest = 30;
        for (int a = 1; a < 13; a++) {
            for (i = 19; i >= 0; i--) {
                if (gv.getTotalBlock()[i][a] == 1) {
                    if (highest > i) {
                        highest = i;
                    }
                }
            }
        }
        this->SetColor(DARK_GRAY);
        for (i = 19; i >= highest; i--) {
            for (j = 0; j < 14; j++) {
                if (j == 0 || j == 13 || i == 20)		//레벨에 따라 외벽 색이 변함
                {
                    if (i == MAX_LIMIT && level == 3) {
                        this->SetColor(RED);
                    } else if (i == MAX_LIMIT - 6 && level == 3) {
                        this->SetColor(DARK_RED);
                    } else {
                        this->SetColor((gv.getLevel() % 6) + 1);
                    }
                } else {
                    if (level == 1)
                        this->SetColor(gv.getTotalBlock()[i][j]);
                    else this->SetColor(DARK_GRAY);
                }

                this->gotoxy((j * 2) + gv.getAbsoluteX(), i + gv.getAbsoluteY());
                if (gv.getTotalBlock()[i][j] == 1) {
                    cout << "■";
                }
            }
        }
        this->SetColor(BLACK);
        this->gotoxy(77, 23);
    }
    return 0;
}

int GameUIManager::show_total_block(const int& level) {
    int i, j;
//	this->SetColor(DARK_GRAY);
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 14; j++) {
            if (j == 0 || j == 13 || i == 20)		//레벨에 따라 외벽 색이 변함
            {
                if (i == MAX_LIMIT && level == 3) {
                    this->SetColor(RED);
                } else if (i == MAX_LIMIT - 6 && level == 3) {
                    this->SetColor(DARK_RED);
                } else {
                    this->SetColor((gv.getLevel() % 6) + 1);
                }
            } else {
                if(level==1)
                    this->SetColor(gv.getTotalBlock()[i][j]);
                else this->SetColor(DARK_GRAY);
            }

            // Not checked from now.
            this->gotoxy((j * 2) + gv.getAbsoluteX(), i + gv.getAbsoluteY());

            if (gv.getTotalBlock()[i][j] !=0) {
                cout << "■";
            } else {
                cout << "  ";
            }

        }
    }
    this->SetColor(BLACK);
    this->gotoxy(77, 23);
    return 0;
}

int GameUIManager::show_next_block(const int& level, const int& shape) {

    int i, j;
    int limit_x1, limit_x2, limit_y1, limit_y2;
    this->SetColor((gv.getLevel() + 1) % 6 + 1);

    ////수정한것
    if (level == 2 || level == 4) {
        limit_x1 = 1;
        limit_x2 = 7;
        limit_y1 = 0;
        limit_y2 = 6;
    } else {
        limit_x1 = 1;
        limit_x2 = 6;
        limit_y1 = 0;
        limit_y2 = 5;
    }

    for (i = 1; i < (limit_x2 + 1); i++) {
        this->gotoxy(33, i);
        for (j = 0; j < (limit_y2 + 1); j++) {
            if (i == limit_x1 || i == limit_x2 || j == limit_y1 || j == limit_y2) {
                cout << "■";
            } else {
                cout << "  ";
            }

        }
    }
    show_cur_block(level, shape, 0, 15, 1, false);
    return 0;
}

int GameUIManager::show_logo() {
    int i, j;



    SetColor(SKY_BLUE);

    this->gotoxy(20, 3);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    Sleep(10);
    this->gotoxy(28, 18);
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";


    SetColor(VOILET);
    Sleep(100);
    this->gotoxy(25, 13);
    cout << "     ■■■ ■■■■ ■■■■■ ■■■ ■■■ ■■■■ ■  ■ ";
    Sleep(100);
    this->gotoxy(25, 14);
    cout << "     ■     ■    ■ ■  ■  ■ ■  ■ ■  ■ ■    ■  ■■  ";
    Sleep(100);
    this->gotoxy(25, 15);
    cout << "     ■     ■    ■ ■  ■  ■ ■■■ ■■■ ■    ■   ■   ";
    Sleep(100);
    this->gotoxy(25, 16);
    cout << "     ■■■ ■■■■ ■  ■  ■ ■     ■  ■ ■    ■   ■   ■";


    SetColor(GREEN);
    this->gotoxy(20, 5);
    cout << "     ■■■■■   ■■■■■  ■■■■  ■■■■  ■■  ■■ ";
    Sleep(100);
    this->gotoxy(20, 6);
    cout << "   ■        ■   ■      ■  ■        ■         ■    ■  ";
    Sleep(100);
    this->gotoxy(20, 7);
    cout << "   ■             ■      ■  ■        ■         ■■  ■  ";
    Sleep(100);
    this->gotoxy(20, 8);
    cout << "   ■    ■■■   ■■■■■  ■■■■  ■■■■   ■ ■ ■  ";
    Sleep(100);
    this->gotoxy(20, 9);
    cout << "   ■        ■   ■ ■       ■        ■         ■  ■■  ";
    Sleep(100);
    this->gotoxy(20, 10);
    cout << "   ■        ■   ■   ■     ■        ■         ■    ■ ";
    Sleep(100);
    this->gotoxy(20, 11);
    cout << "     ■■■■■ ■■■  ■■  ■■■■  ■■■■  ■■  ■■ ";


    this->gotoxy(40, 25);
    cout << "Please Press Any Key~!";



    for (i = 0; 1; i++) {
        if (i % 40 == 0) { // So this is the change-rate(Refresh rate) of Logo

            for (j = 0; j < 5; j++) {
                this->gotoxy(13, 20 + j);
                cout << "                                                                           ";
            }

            show_cur_block(3, rand() % 7, rand() % 4, 13, 20, false);
            show_cur_block(3, rand() % 7, rand() % 4, 19, 20, false);
            show_cur_block(3, rand() % 7, rand() % 4, 26, 20, false);
            show_cur_block(3, rand() % 7, rand() % 4, 31, 20, false);
        }
        if (kbhit()) // maybe able to change kbhit to getche?
            break;

        /**
         * The fresh-rate
         * 30ms + (The time in Counter which exceeds 40 * something)
         */
        Sleep(30); // in ms
    }

    // We Entered something. Clear it in buffer.
    getche();
    system("cls");

    return 0;
}

int GameUIManager::show_gamestat() {
    static int printed_text = 0;
    this->SetColor(GRAY);
    if (printed_text == 0) {
        this->gotoxy(35, 10);
        cout << "STAGE";

        this->gotoxy(35, 12);
        cout << "SCORE";

        this->gotoxy(35, 15);
        cout << "LINES";
    }
    this->gotoxy(41, 10);
    cout << gv.getLevel() + 1;
    this->gotoxy(35, 13);
    cout << setw(10) << gv.getScore();
    this->gotoxy(35, 16);
    cout << setw(10) << gv.getStageInformation()[gv.getLevel()].getClearLine() - gv.getLine();
    return 0;
}

int GameUIManager::show_gameover() {
    this->SetColor(RED);
    this->gotoxy(15, 8);
    cout << "┏━━━━━━━━━━━━━┓";
    this->gotoxy(15, 9);
    cout << "┃**************************┃";
    this->gotoxy(15, 10);
    cout << "┃*        GAME OVER       *┃";
    this->gotoxy(15, 11);
    cout << "┃**************************┃";
    this->gotoxy(15, 12);
    cout << "┗━━━━━━━━━━━━━┛";
    fflush(stdin);
    Sleep(1000);

    getche();
    system("cls");

    return 0;
}

void GameUIManager::SetColor(const int& color) {
    static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(std_output_handle, color);
}

int GameUIManager::gotoxy(const int& x, const int& y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.Y = y;
    pos.X = x;
    SetConsoleCursorPosition(hConsole, pos);
    return 0;
}

void GameUIManager::setCursorView(bool visible) {
    CONSOLE_CURSOR_INFO cursor = { 1, visible };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
