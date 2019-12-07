#pragma warning(disable:4996)
#include <ctime>
#include "GameManager.h"
#include "User.h"

int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    system("color 7");
    GameManager gm;
    gm.userUI();
    return 0;
}