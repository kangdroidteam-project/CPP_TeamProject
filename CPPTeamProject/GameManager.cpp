#include "GameManager.h"

void GameManager::play() {
    char keytemp;
    GlobalVariant gv;
    GameUIManager gui(gv);
    TetrisCore tc(gui, gv);
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
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX() + gv.getCtr(), gv.getBlockY());
                            gv.setBlockAngle((gv.getBlockAngle() + 1) % 4);
                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        }
                        break;
                    case KEY_LEFT:		//왼쪽으로 이동
                        if (gv.getBlockX() > 1) {
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                            gv.setBlockX((gv.getBlockX() - 1));
                            if (tc.strike_check(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), 0) == 1)
                                gv.setBlockX((gv.getBlockX() + 1));


                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        }
                        break;
                    case KEY_RIGHT:		//오른쪽으로 이동
                        if (gv.getBlockX() < 14) {
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                            gv.setBlockX((gv.getBlockX() + 1));
                            if (tc.strike_check(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), 0) == 1) {
                                gv.setBlockX((gv.getBlockX() - 1));
                            }
                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        }
                        break;
                    case KEY_DOWN:		//아래로 이동
                        gv.setGameOver(tc.move_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape()));
                        gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        break;
                    }
                } else if (keytemp == 32) { //스페이스바를 눌렀을때
                    while (gv.getGameOver() == 0) {
                        gv.setGameOver(tc.move_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape()));
                    }
                    gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                } else {
                    // Clear out 
                    gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                    gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                }
            }
            if (i % gv.getStageInformation()[gv.getLevel()].getSpeed() == 0) {
                gv.setGameOver(tc.move_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY(), gv.getNextBlockShape()));

                gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
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
