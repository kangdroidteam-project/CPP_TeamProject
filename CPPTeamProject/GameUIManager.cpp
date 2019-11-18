#include "GameUIManager.h"
#include "GlobalVariant.h"
GameUIManager::GameUIManager(GlobalVariant& input) : gv(input) {
}
int GameUIManager::show_cur_block(int shape, int angle, int x, int y) {
    int i, j; // The iteration variable. - Could be localized.

    // Set Color based on block shape.
    switch (shape) {
    case 0:
        SystemUIManager::SetColor(RED);
        break;
    case 1:
        SystemUIManager::SetColor(BLUE);
        break;
    case 2:
        SystemUIManager::SetColor(SKY_BLUE);
        break;
    case 3:
        SystemUIManager::SetColor(WHITE);
        break;
    case 4:
        SystemUIManager::SetColor(YELLOW);
        break;
    case 5:
        SystemUIManager::SetColor(VOILET);
        break;
    case 6:
        SystemUIManager::SetColor(GREEN);
        break;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if ((j + y) < 0) // Absolute starting point of y + j < 0
                continue;

            // Somewhat print damn thing
            if (getBlock()[shape][angle][j][i] == 1) {
                SystemUIManager::gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                cout << "■";

            }
        }
    }
    SystemUIManager::SetColor(BLACK);
    SystemUIManager::gotoxy(77, 23);
    return 0;
}

//Erase current block information(More likely, override with spaces)
int GameUIManager::erase_cur_block(int shape, int angle, int x, int y) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (getBlock()[shape][angle][j][i] == 1) {
                SystemUIManager::gotoxy((i + x) * 2 + gv.getAbsoluteX(), j + y + gv.getAbsoluteY());
                cout << "  ";
                //break;

            }
        }
    }
    return 0;
}
int GameUIManager::show_total_block() {
    int i, j;
    SystemUIManager::SetColor(DARK_GRAY);
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 14; j++) {
            if (j == 0 || j == 13 || i == 20)		//레벨에 따라 외벽 색이 변함
            {
                SystemUIManager::SetColor((gv.getLevel() % 6) + 1);

            } else {
                SystemUIManager::SetColor(DARK_GRAY);
            }

            // Not checked from now.
            SystemUIManager::gotoxy((j * 2) + gv.getAbsoluteX(), i + gv.getAbsoluteY());
            if (gv.total_block[i][j] == 1) {
                cout << "■";
            } else {
                cout << "  ";
            }

        }
    }
    SystemUIManager::SetColor(BLACK);
    SystemUIManager::gotoxy(77, 23);
    return 0;
}

/**
 * Show next block on Top-Right.
 * It basically make box and IN THAT BOX, they show next block.
 * Shape is previously created by make_new_block();
 */
int GameUIManager::show_next_block(int shape) {
    int i, j;
    SystemUIManager::SetColor((gv.getLevel() + 1) % 6 + 1);
    for (i = 1; i < 7; i++) {
        SystemUIManager::gotoxy(33, i);
        for (j = 0; j < 6; j++) {
            if (i == 1 || i == 6 || j == 0 || j == 5) {
                cout << "■";
            } else {
                cout << "  ";
            }

        }
    }
    // So it would show block created by make_new_block();
    show_cur_block(shape, 0, 15, 1);
    return 0;
}

int GameUIManager::show_logo() {
    int i, j;
    SystemUIManager::gotoxy(13, 3);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
    Sleep(100);
    SystemUIManager::gotoxy(13, 4);
    printf("┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆    ◆◆  ┃");
    Sleep(100);
    SystemUIManager::gotoxy(13, 5);
    printf("┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆    ┃");
    Sleep(100);
    SystemUIManager::gotoxy(13, 6);
    printf("┃  ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃");
    Sleep(100);
    SystemUIManager::gotoxy(13, 7);
    printf("┃  ◆    ◆        ◆     ◆ ◆    ◆      ◆  ┃");
    Sleep(100);
    SystemUIManager::gotoxy(13, 8);
    printf("┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆    ◆◆  ┃");
    Sleep(100);
    SystemUIManager::gotoxy(13, 9);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
    SystemUIManager::gotoxy(28, 20);
    cout << "Please Press Any Key~!";

    for (i = 0; 1; i++) {
        if (i % 40 == 0) { // So this is the change-rate(Refresh rate) of Logo

            for (j = 0; j < 5; j++) {
                SystemUIManager::gotoxy(6, 14 + j);
                cout << "                                                          ";
            }

            show_cur_block(rand() % 7, rand() % 4, 6, 14);
            show_cur_block(rand() % 7, rand() % 4, 12, 14);
            show_cur_block(rand() % 7, rand() % 4, 19, 14);
            show_cur_block(rand() % 7, rand() % 4, 24, 14);
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
    SystemUIManager::SetColor(GRAY);
    if (printed_text == 0) {
        SystemUIManager::gotoxy(35, 7);
        cout << "STAGE";

        SystemUIManager::gotoxy(35, 9);
        cout << "SCORE";

        SystemUIManager::gotoxy(35, 12);
        cout << "LINES";
    }
    SystemUIManager::gotoxy(41, 7);
    cout << gv.getLevel() + 1;
    SystemUIManager::gotoxy(35, 10);
    cout << gv.getScore();
    SystemUIManager::gotoxy(35, 13);
    cout << gv.stage_data[gv.getLevel()].getClearLine() - gv.getLine();
    return 0;
}

int GameUIManager::show_gameover() {
    SystemUIManager::SetColor(RED);
    SystemUIManager::gotoxy(15, 8);
    cout << "┏━━━━━━━━━━━━━┓";
    SystemUIManager::gotoxy(15, 9);
    cout << "┃**************************┃";
    SystemUIManager::gotoxy(15, 10);
    cout << "┃*        GAME OVER       *┃";
    SystemUIManager::gotoxy(15, 11);
    cout << "┃**************************┃";
    SystemUIManager::gotoxy(15, 12);
    cout << "┗━━━━━━━━━━━━━┛";
    fflush(stdin);
    Sleep(1000);

    getche();
    system("cls");

    return 0;
}

int GameUIManager::input_data() {
    int i = 0; // checking variable for input(level)
    SystemUIManager::SetColor(GRAY);
    SystemUIManager::gotoxy(10, 7);
    cout << "┏━━━━<GAME KEY>━━━━━┓";
    Sleep(10);
    SystemUIManager::gotoxy(10, 8);
    cout << "┃ UP   : Rotate Block        ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 9);
    cout << "┃ DOWN : Move One-Step Down  ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 10);
    cout << "┃ SPACE: Move Bottom Down    ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 11);
    cout << "┃ LEFT : Move Left           ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 12);
    cout << "┃ RIGHT: Move Right          ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 13);
    cout << "┗━━━━━━━━━━━━━━┛";

    // i is checking variable for input(level)
    while (i < 1 || i>8) {
        SystemUIManager::gotoxy(10, 3);
        cout << "Select Start level[1-8]:       \b\b\b\b\b\b\b";
        scanf("%d", &i);
        while (getchar() != '\n');
    }

    gv.setLevel(i - 1); // For index.
    system("cls");
    return 0;
}
