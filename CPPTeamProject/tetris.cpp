#pragma warning(disable:4996)
#include <ctime>
#include "GameManager.h"

int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    GameManager gm;
    int input;
    do {
        cout << "1. Normal Tetris Game;" << endl;
        cout << "2. The Centrum Game;" << endl;
        cin >> input;
        switch (input) {
        case 1:
            gm.play(false);
            break;
        case 2:
            gm.play(true);
            break;
        }
    } while (input != 3);
    return 0;
}