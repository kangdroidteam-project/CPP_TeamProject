#include "GameManager.h"

void GameManager::play() {
    char keytemp;
    GlobalVariant gv;
    GameUIManager gui(gv);
    TetrisCore tc(gui, gv);
    tc.init(); // Initiate.
    gui.show_logo();
    while (1) {

        gui.input_data();
        gui.show_total_block();
        gv.setBlockShape(tc.make_new_block());
        gv.setNextBlockShape(tc.make_new_block());
        gui.show_next_block(gv.getNextBlockShape()); // Show next block
        tc.block_start(gv.getPtrBlockAngle(), gv.getPtrBlockX(), gv.getPtrBlockY()); // Start from first block. - gv.getBlockShape() = first block. Inits coord/angle.
        gui.show_gamestat();
        for (int i = 1; 1; i++) {
            if (kbhit()) {
                keytemp = getche();
                if (keytemp == EXT_KEY) {
                    keytemp = getche();
                    switch (keytemp) {
                    case KEY_UP:		//회전하기
                        gv.setCtr(0);
                        if (tc.strike_check(gv.getBlockShape(), (gv.getBlockAngle() + 1) % 4, gv.getPtrBlockX(), gv.getBlockY(), 1) == 0) {
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX() + gv.getCtr(), gv.getBlockY());
                            gv.setBlockAngle((gv.getBlockAngle() + 1) % 4);
                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        }
                        break;
                    case KEY_LEFT:		//왼쪽으로 이동
                        if (gv.getBlockX() > 1) {
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                            gv.setBlockX((gv.getBlockX() - 1));
                            if (tc.strike_check(gv.getBlockShape(), gv.getBlockAngle(), gv.getPtrBlockX(), gv.getBlockY(), 0) == 1)
                                gv.setBlockX((gv.getBlockX() + 1));


                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        }
                        break;
                    case KEY_RIGHT:		//오른쪽으로 이동
                        if (gv.getBlockX() < 14) {
                            gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                            gv.setBlockX((gv.getBlockX() + 1));
                            if (tc.strike_check(gv.getBlockShape(), gv.getBlockAngle(), gv.getPtrBlockX(), gv.getBlockY(), 0) == 1) {
                                gv.setBlockX((gv.getBlockX() - 1));
                            }
                            gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        }
                        break;
                    case KEY_DOWN:		//아래로 이동
                        gv.setGameOver(tc.move_block(gv.getPtrBlockShape(), gv.getPtrBlockAngle(), gv.getPtrBlockX(), gv.getPtrBlockY(), gv.getPtrNextBlockShape()));
                        gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                        break;
                    }
                } else if (keytemp == 32) { //스페이스바를 눌렀을때
                    while (gv.getGameOver() == 0) {
                        gv.setGameOver(tc.move_block(gv.getPtrBlockShape(), gv.getPtrBlockAngle(), gv.getPtrBlockX(), gv.getPtrBlockY(), gv.getPtrNextBlockShape()));
                    }
                    gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                } else {
                    // Clear out 
                    gui.erase_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                    gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
                }
            }
            if (i % gv.stage_data[gv.getLevel()].getSpeed() == 0) {
                gv.setGameOver(tc.move_block(gv.getPtrBlockShape(), gv.getPtrBlockAngle(), gv.getPtrBlockX(), gv.getPtrBlockY(), gv.getPtrNextBlockShape()));

                gui.show_cur_block(gv.getBlockShape(), gv.getBlockAngle(), gv.getBlockX(), gv.getBlockY());
            }

            if (gv.getGameOver() == 1) {
                gui.show_gameover();
                SystemUIManager::SetColor(GRAY);
                break;
            }

            SystemUIManager::gotoxy(77, 23);
            Sleep(15);
            SystemUIManager::gotoxy(77, 23);
        }
        tc.init();
    }
}
