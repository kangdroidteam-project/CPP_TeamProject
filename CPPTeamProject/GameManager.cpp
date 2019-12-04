#include "GameManager.h"

void GameManager::play() {
    char keytemp;
    GlobalVariant gv;
    BlockManager bm;
    GameUIManager gui(gv,bm);
    TetrisCore tc(gui, gv,bm);
    tc.init(); // Initiate.
    gui.show_logo();
    while (true) {	

        int level = 5;
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
                                gui.erase_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX() + gv.getCtr(), gv.getBlockY());
                                int origin_angle;
                                gv.setBlockAngle((gv.getBlockAngle() + 1) % 4);
                                gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                            }
                            break;
                        }
                        else continue;
                    case KEY_LEFT:		//왼쪽으로 이동
                        if (true) {
                            gui.erase_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                            gv.setBlockX((gv.getBlockX() - 1));
                            if (tc.strike_check(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), 0) == 1)
                                gv.setBlockX((gv.getBlockX() + 1));

                            gui.show_cur_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        }
                        break;
                    case KEY_RIGHT:		//오른쪽으로 이동
                        if (gv.getBlockX() < 14) {
                            gui.erase_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                            gv.setBlockX((gv.getBlockX() + 1));
                            if (tc.strike_check(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), 0) == 1) {
                                gv.setBlockX((gv.getBlockX() - 1));
                            }
                            gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        }
                        break;
                    case KEY_DOWN:		//아래로 이동
                        gv.setGameOver(tc.move_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape()));
                        gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        break;
                    }
                }
                else if (keytemp == 32) { //스페이스바를 눌렀을때
                    while (gv.getGameOver() == 0) {
                        gv.setGameOver(tc.move_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape()));
                    }
                    gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                }
                else {
                    // Clear out 
                    gui.erase_cur_block(level, gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                    gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                }
            }
            if (i % gv.getStageInformation()[gv.getLevel()].getSpeed() == 0) {
                gv.setGameOver(tc.move_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape()));

                gui.show_cur_block(level,gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
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
