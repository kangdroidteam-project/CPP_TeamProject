#include "GameUIManager.h"
#include "GlobalVariant.h"
#include "BlockManager.h"

GameUIManager::GameUIManager(GlobalVariant& input, BlockManager& block) : gv(input),bm(block){
}
int GameUIManager::show_cur_block(const int& level, const int& shape, const int& angle, const int& x, const int& y) {
    int i, j; // The iteration variable. - Could be localized.

    int levelx;
    int levely; 

    gv.getlevelXY(level, levelx, levely);

    // Set Color based on block shape.
    switch (shape) {
    case 0:
        this->SetColor(RED);
        break;
    case 1:
        this->SetColor(BLUE);
        break;
    case 2:
        this->SetColor(SKY_BLUE);
        break;
    case 3:
        this->SetColor(WHITE);
        break;
    case 4:
        this->SetColor(YELLOW);
        break;
    case 5:
        this->SetColor(VOILET);
        break;
    case 6:
        this->SetColor(GREEN);
        break;
    }

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
    case 2:
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
    case 4:
        for (i = 0; i < levelx; i++) {
            for (j = 0; j < levely; j++) {

                if ((j + y) < 0) // Absolute starting point of y + j < 0
                    continue;

                if (bm.getThirdBlock()[shape][angle][j][i] != 0) {
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
int GameUIManager::erase_cur_block(const int& level, const int& shape, const int& angle, const int& x, const int& y) {
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
    case 2:
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
    case 4:

        for (i = 0; i < lx; i++) {
            for (j = 0; j < ly; j++) {
                if (bm.getThirdBlock()[shape][angle][j][i] != 0) {
                    this->gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                    cout << "  ";
                    //break;

                }
            }
        }
        break;
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
                this->SetColor((gv.getLevel() % 6) + 1);
            }
            else {
                if(level==1)
                    this->SetColor(gv.getTotalBlock()[i][j]);
                else this->SetColor(DARK_GRAY);
            }

            // Not checked from now.
            this->gotoxy((j * 2) + gv.getAbsoluteX(), i + gv.getAbsoluteY());
            if (gv.getTotalBlock()[i][j] !=0) {
//				if (getBlock()[gv.getBlockShape()][gv.getBlockAngle()][i][j] != -1) {
//					this->SetColor(getBlock()[gv.getBlockShape()][gv.getBlockAngle()][2][3]);
//					cout << "■";
//				}
//				else {
                    cout << "■";
                }
            
            else {
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
    this->SetColor((gv.getLevel() + 1) % 6 + 1);
    for (i = 1; i < 7; i++) {
        this->gotoxy(33, i);
        for (j = 0; j < 6; j++) {
            if (i == 1 || i == 6 || j == 0 || j == 5) {
                cout << "■";
            }
            else {
                cout << "  ";
            }

        }
    }
    show_cur_block(level, shape, 0, 15, 1);
    return 0;
}

int GameUIManager::show_logo() {
    int i, j;
    this->SetColor(WHITE);
    this->gotoxy(13, 3);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━┓";
    Sleep(100);
    this->gotoxy(13, 4);
    cout << "┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆    ◆◆  ┃";
    Sleep(100);
    this->gotoxy(13, 5);
    cout << "┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆    ┃";
    Sleep(100);
    this->gotoxy(13, 6);
    cout << "┃  ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃";
    Sleep(100);
    this->gotoxy(13, 7);
    cout << "┃  ◆    ◆        ◆     ◆ ◆    ◆      ◆  ┃";
    Sleep(100);
    this->gotoxy(13, 8);
    cout << "┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆    ◆◆  ┃";
    Sleep(100);
    this->gotoxy(13, 9);
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━┛";
    this->gotoxy(28, 20);
    cout << "Please Press Any Key~!";

    for (i = 0; 1; i++) {
        if (i % 40 == 0) { // So this is the change-rate(Refresh rate) of Logo

            for (j = 0; j < 5; j++) {
                this->gotoxy(6, 14 + j);
                cout << "                                                          ";
            }

            show_cur_block(3,rand() % 7, rand() % 4, 6, 14);
            show_cur_block(3,rand() % 7, rand() % 4, 12, 14);
            show_cur_block(3,rand() % 7, rand() % 4, 19, 14);
            show_cur_block(3,rand() % 7, rand() % 4, 24, 14);
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
        this->gotoxy(35, 7);
        cout << "STAGE";

        this->gotoxy(35, 9);
        cout << "SCORE";

        this->gotoxy(35, 12);
        cout << "LINES";
    }
    this->gotoxy(41, 7);
    cout << gv.getLevel() + 1;
    this->gotoxy(35, 10);
    cout << setw(10) << gv.getScore();
    this->gotoxy(35, 13);
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

int GameUIManager::input_data() {
    int i = 0; // checking variable for input(level)
    this->SetColor(GRAY);
    this->gotoxy(10, 7);
    cout << "┏━━━━<GAME KEY>━━━━━┓";
    Sleep(10);
    this->gotoxy(10, 8);
    cout << "┃ UP   : Rotate Block        ┃";
    Sleep(10);
    this->gotoxy(10, 9);
    cout << "┃ DOWN : Move One-Step Down  ┃";
    Sleep(10);
    this->gotoxy(10, 10);
    cout << "┃ SPACE: Move Bottom Down    ┃";
    Sleep(10);
    this->gotoxy(10, 11);
    cout << "┃ LEFT : Move Left           ┃";
    Sleep(10);
    this->gotoxy(10, 12);
    cout << "┃ RIGHT: Move Right          ┃";
    Sleep(10);
    this->gotoxy(10, 13);
    cout << "┗━━━━━━━━━━━━━━┛";


    while (i < 1 || i>10) {
        this->gotoxy(10, 3);
        cout << "Select Start level[1-10]:       \b\b\b\b\b\b\b";
        cin >> i;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        this->gotoxy(24, 3);
        cout << "                                                                                                ";
    }

    gv.setLevel(i - 1); // For index.
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
