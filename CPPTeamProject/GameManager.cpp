#include "GameManager.h"

void GameManager::test() {
    fake_y = -3;
    int p_val = 0;

    while (p_val == 0) {
        p_val = tc.move_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, gv.getNextBlockShape(), true);
    }
    gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, true);
}

void GameManager::printThis() {
    fake_y = -3;
    //gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, true);
    int p_val = 0;

    while (p_val == 0) {
        p_val = tc.move_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, gv.getNextBlockShape(), true);
    }
    gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, true);
}

void GameManager::play() {
    char keytemp;
    tc.init(); // Initiate.
    gui.show_logo();
    while (true) {

        gui.input_data();
        gui.show_total_block();
        gv.setBlockShape(tc.make_new_block());
        gv.setNextBlockShape(tc.make_new_block());
        gui.show_next_block(gv.getNextBlockShape()); // Show next block
        tc.block_start(gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY()); // Start from first block. - gv.getBlockShape() = first block. Inits coord/angle.
        gui.show_gamestat();
        for(int i = 0; true; i++) {

            if (kbhit()) {
                keytemp = getche();
                if (keytemp == EXT_KEY) {
                    keytemp = getche();
                    switch (keytemp) {
                    case KEY_UP:		//회전하기
                        gv.setCtr(0);
                        if (tc.strike_check(gv.getBlockShape(), (gv.getBlockAngle() + 1) % 4, gv.getBlockX(), gv.getBlockY(), 1) == 0) {
                            test();
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX() + gv.getCtr(), gv.getBlockY(), false);
                            gv.setBlockAngle((gv.getBlockAngle() + 1) % 4);
                            printThis();
                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                            
                        }
                        break;
                    case KEY_LEFT:		//왼쪽으로 이동
                        if (gv.getBlockX() > 1) {
                            test();
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                            gv.setBlockX((gv.getBlockX() - 1));
                            if (tc.strike_check(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), 0) == 1)
                                gv.setBlockX((gv.getBlockX() + 1));
                            printThis();
                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                            
                        }
                        break;
                    case KEY_RIGHT:		//오른쪽으로 이동
                        if (gv.getBlockX() < 11) {
                            test();
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                            gv.setBlockX((gv.getBlockX() + 1));
                            if (tc.strike_check(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), 0) == 1) {
                                gv.setBlockX((gv.getBlockX() - 1));
                            }
                            printThis();
                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                            
                        }
                        break;
                    case KEY_DOWN:		//아래로 이동
                        gv.setGameOver(tc.move_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape(), false));
                        gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                        break;
                    }
                } else if (keytemp == 32) { //스페이스바를 눌렀을때
                    while (gv.getGameOver() == 0) {
                        gv.setGameOver(tc.move_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape(), false));
                    }
                    gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                } else {
                    // Clear out 
                    test();
                    gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                    gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                }
            }
            if (i % gv.getStageInformation()[gv.getLevel()].getSpeed() == 0) {
                printThis();
                gv.setGameOver(tc.move_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape(), false));
                gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
            }

            if (gv.getGameOver() == 1) {
                gui.show_gameover();
                gui.SetColor(GRAY);
                break;
            }

            gui.gotoxy(77, 23);
            Sleep(15);
            gui.gotoxy(77, 23);
        }
        tc.init();
    }
}
