#include "GameManager.h"

void GameManager::test() {
    fake_y = gv.getBlockY();
    int p_val = 0;

    while (p_val == 0) {
        p_val = tc.move_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, gv.getNextBlockShape(), true);
    }
    gui.erase_cur_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), fake_y, true);
}

void GameManager::printThis() {
    fake_y = gv.getBlockY();
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
        gv.setLevel(5);
        gui.show_total_block(level);
        gv.setBlockShape(tc.make_new_block(level));
        gv.setNextBlockShape(tc.make_new_block(level), level);
        gui.show_next_block(level,gv.getNextBlockShape()); // Show next block
        tc.block_start(level,gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());

        if (level != 1) {
            gui.show_gamestat();
        }

        for (int i = 0; true; i++) {
            if (kbhit()) {
                keytemp = getche();
                if (keytemp == EXT_KEY) {
                    keytemp = getche();
                    switch (keytemp) {
                    case KEY_UP:		//회전하기
                        if (level != 1) {
                            gv.setCtr(0);
                            test();
                            if (tc.strike_check(level,gv.getBlockShape(), (gv.getBlockAngle() + 1) % 4, gv.getBlockX(), gv.getBlockY(), 1) == 0) {
                                
                                gui.erase_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX() + gv.getCtr(), gv.getBlockY(), false);
                                
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
                } else if (keytemp == 32) { //스페이스바를 눌렀을때
                    while (gv.getGameOver() == 0) {
                        gv.setGameOver(tc.move_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape(), false));
                    }
                    gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), false);
                } else if (keytemp == 'u') {
                    if (level == 5) {
                        if (gv.getScore() >= 200) {
                            gv.itemOneTwo(0);
                            gui.show_total_block(level);
                            int l;

                            // KMS SUG
                            for (int k = 0; k < 21; k++) {
                                for (int p = 1; p < 14; p++) {
                                    if (gv.getTotalBlock()[k][p] == 0 && gv.getTotalBlock()[k - 1][p] != 0) {
                                        for (l = k; l > 0; l--) {
                                            gv.setTotalBlock(p, l, gv.getTotalBlock()[l - 1][p]);
                                        }
                                        gv.setTotalBlock(p, 0, 0);
                                    }
                                }
                            } // END
                            gui.show_total_block(level);
                            tc.check_full_line();
                            gv.setScore(gv.getScore() - 200);
                            if (level != 1) {
                                gui.show_gamestat();
                            }
                        } else {
                            // NO MONEY
                        }
                    }
                } else if (keytemp == 'i') {
                    if (level == 5) {
                        if (gv.getScore() >= 100) {
                            gv.itemOneTwo(1);
                            gui.show_total_block(level);
                            tc.check_full_line();
                            gv.setScore(gv.getScore() - 100);
                            if (level != 1) {
                                gui.show_gamestat();
                            }
                        } else {
                            // NO MONEY
                        }
                    }
                } else if (keytemp == 'o') {
                    if (level == 5) {
                        if (gv.getScore() >= 300) {
                            gv.itemThree();
                            gui.show_total_block(level);
                            int l;
                            // KMS SUG
                            for (int k = 0; k < 21; k++) {
                                for (int p = 1; p < 14; p++) {
                                    if (gv.getTotalBlock()[k][p] == 0 && gv.getTotalBlock()[k - 1][p] != 0) {
                                        for (l = k; l > 0; l--) {
                                            gv.setTotalBlock(p, l, gv.getTotalBlock()[l - 1][p]);
                                        }
                                        gv.setTotalBlock(p, 0, 0);
                                    }
                                }
                            } // END
                            gui.show_total_block(level);
                            tc.check_full_line();
                            gv.setScore(gv.getScore() - 300);
                            if (level != 1) {
                                gui.show_gamestat();
                            }
                        } else {
                            // NO MONEY
                        }
                    }
                } else {
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

            // 12 is the one.
            if (level == 3) {
                if (tc.test_val == 1) {
                    if (tc.check_tw_floor()) {
                        // check empty spaces.
                        if (tc.check_empty_space() == false) {
                            gui.show_gameover();
                            gui.SetColor(GRAY);
                        } else {
                            // Game passed.
                            cout << "Game Passed!" << endl;
                            system("cls");
                        }
                        break;
                    }
                }
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
