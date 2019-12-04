#include "GameManager.h"

void GameManager::test() {
    fake_y = -3;
    int p_val = 0;

    while (p_val == 0) {
        p_val = tc.move_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, gv.getNextBlockShape(), true);
    }
    gui.erase_cur_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, true);
}

void GameManager::printThis() {
    fake_y = -3;
    //gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, true);
    int p_val = 0;

    while (p_val == 0) {
        p_val = tc.move_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, gv.getNextBlockShape(), true);
    }
    gui.show_cur_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, true);
}

void GameManager::play() {
    char keytemp;
    tc.init(); // Initiate.
    gui.show_logo();
    while (true) {
        //level (0~4)
        //0 : 모스부호 
        //1 : 애니팡
        //2 : 모음
        //3 : 센트롬
        //4: 자음
        //5 : 보통게임

        gui.input_data();
        gui.show_total_block(0);
        gv.setBlockShape(tc.make_new_block(level));
        gv.setNextBlockShape(tc.make_new_block(level));
        gui.show_next_block(level,gv.getNextBlockShape()); // Show next block
        tc.block_start(level,gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());

        for (int i = 0; true; i++) {
            if (kbhit()) {
                keytemp = getche();
                if (keytemp == EXT_KEY) {
                    keytemp = getche();
                    switch (keytemp) {
                    case KEY_UP:		//회전하기
                        if (level != 1) {
                            gv.setCtr(0);
                            if (tc.strike_check(level,gv.getBlockShape(), (gv.getBlockAngle() + 1) % 4, gv.getBlockX(), gv.getBlockY(), 1) == 0) {
                                gui.erase_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX() + gv.getCtr(), gv.getBlockY(), false);
                                test();
                                int origin_angle;
                                gv.setBlockAngle((gv.getBlockAngle() + 1) % 4);
                                printThis();
                                gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                            }
                            break;
                        }
                        else continue;
                    case KEY_LEFT:		//왼쪽으로 이동
                        if (true) {
                            test();
                            gui.erase_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                            gv.setBlockX((gv.getBlockX() - 1));
                            if (tc.strike_check(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), 0) == 1)
                                gv.setBlockX((gv.getBlockX() + 1));

                            printThis();
                            gui.show_cur_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                        }
                        break;
                    case KEY_RIGHT:		//오른쪽으로 이동
                        if (gv.getBlockX() < 14) {
                            test();
                            gui.erase_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                            gv.setBlockX((gv.getBlockX() + 1));
                            if (tc.strike_check(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), 0) == 1) {
                                gv.setBlockX((gv.getBlockX() - 1));
                            }
                            printThis();
                            gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                        }
                        break;
                    case KEY_DOWN:		//아래로 이동
                        gv.setGameOver(tc.move_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape(), false));
                        gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                        break;
                    }
                }
                else if (keytemp == 32) { //스페이스바를 눌렀을때
                    while (gv.getGameOver() == 0) {
                        gv.setGameOver(tc.move_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape(), false));
                    }
                    gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                }
                else {
                    // Clear out 
                    test();
                    gui.erase_cur_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                    gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                }
            }
            if (i % gv.getStageInformation()[gv.getLevel()].getSpeed() == 0) {
                printThis();
                gv.setGameOver(tc.move_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape(), false));

                gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
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
