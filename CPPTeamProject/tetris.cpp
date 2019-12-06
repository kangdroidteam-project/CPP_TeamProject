#pragma warning(disable:4996)
#include <ctime>
#include "GameManager.h"


int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    GameManager gm;
    gm.story();
    return 0;
}