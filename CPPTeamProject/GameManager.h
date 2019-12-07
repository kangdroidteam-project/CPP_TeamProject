#pragma once
#include "GameUIManager.h"
#include "TetrisCore.h"
#include "BlockManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
class GameManager {
private:
    GlobalVariant gv;
    BlockManager bm;
    GameUIManager gui;
    TetrisCore tc;
    int fake_y;
    int level;
    int save; // 0 - prologue, 1 - morse
public:
    GameManager() : gv(), bm(), gui(gv, bm), tc(gui, gv, bm) {
        gui.setCursorView(false);
    }
    void test();
    bool play(int level);
    void printThis();

    void getInput() {
        gui.SetColor(WHITE);
        gui.gotoxy(40, 25);
        cout << "Please Press Any Key~!";
        getche();
    }

    void money() {
        gui.gotoxy(90, 3);
        cout << "MONEY : " << gv.getScore();
    }

    void story() {

        bool flag;
        tc.init();

        gui.show_logo();
        // <챔스 브금>
        PlaySound(TEXT("Champs_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);

        //<진짜 시작 브금>

        while (true) {
            int x = 17;
            int y = 5;
            if (save <= 0) {
                //prologue
                gui.SetColor(WHITE);
                money();
                gui.gotoxy(x, y);
                cout << "우리 회사는 건국대학교 19학번 소프트웨어학과 출신으로 이루어진 신생기업 Green Company이다.";
                gui.gotoxy(x, (y += 2));
                cout << "사장 1명과 개발자 직원 1명으로 운영되고 있다.";
                gui.gotoxy(x, (y += 2));
                cout << "현재 Green Company는 자금이 많이 부족한 신생기업이다.";
                gui.gotoxy(x, (y += 2));
                cout << "그리하여 많은 회의를 통해 테트리스 게임을 만들어 돈을 벌 계획을 세운다.";
                gui.gotoxy(x, (y += 2));
                cout << "그러나 신생기업이라서 돈이 부족한 기업은 돈이 없음에도 불구하고 코드를 사기로 결정한다. ";
                gui.gotoxy(x, (y += 2));
                cout << "이를 알게된 경쟁 기업 BLue Company는 Green Company가 만든 테트리스 게임 코드를";
                gui.gotoxy(x, (y += 2));
                cout << "훔쳐가 버그를 잔뜩 남겨놓고 떠난다.";
                gui.gotoxy(x, (y += 2));
                cout << "암울한 상황 속에서 직원은 테트리스 게임을 실행해본다.";

                getInput();

                //게임 1 (모스부호)
                //<게임 1 브금>
                system("cls");
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game1BGM.wav"), NULL, SND_LOOP | SND_ASYNC);
                this->level = 0;
                money();
                flag = play(0);

                if (flag) {
                    //<리얼 oh 브금>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("real oh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    system("cls");
                    gui.SetColor(WHITE);
                    money();
                    gui.gotoxy(28, 12);
                    cout << "시작이 절반이야. 조금씩 버그를 고쳐나가보자." << endl;
                    save = 1;
                } else {
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gameover();
                    system("cls");
                    gui.SetColor(WHITE);
                    //<GG 효과음, 괴물쥐 효과음, 조커 브금>
                    gui.SetColor(WHITE);
                    gui.gotoxy(28, 14);
                    cout << "이런 쉬운 코드조차 해결하지 못하다니,,,,";
                    gui.gotoxy(28, 16);
                    cout << "파산. 다시 시도해보겠습니까?(y/n)";
                    char t = getchar();
                    while (getchar() != '\n');
                    system("cls");

                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }
                getInput();
                // Clear CMD
                system("cls");
            }

            if (save <= 1) {
                x = 17;
                y = 9;
                money();
                //광산 가기 전
                gui.gotoxy(x, y);
                cout << "자금이 부족한 기업을 살리기 위해 사장이 돈을 벌어와야 하는 상황이 되었다.";
                gui.gotoxy(x, (y += 2));
                cout << "사장은 결국 단기간 고소득인 광산으로 가서 보석들을 캐며 일일 아르바이트를 하게 되었다.";
                gui.gotoxy(x, (y += 2));
                cout << "광부가 가져와야할 보석들의 개수를 지정해주고, 그것을 충족시켜야 급여를 받을 수 있다.";
                gui.gotoxy(x, (y += 2));
                cout << "그렇게 사장은 회사를 살리겠다는 일념 하에 광산에 들어갔다.";
                getInput();

                system("cls");
                x = 17;
                y = 9;
                money();
                gui.SetColor(RED);
                gui.gotoxy(x, y);
                cout << "테트리스 형식과 같지만, 광물들은 깨지기 쉬워 회전이 불가능하다. " << endl;
                gui.gotoxy(x, (y += 2));
                cout << "같은 색의 광물이 4개 이상 붙어있어야 채굴이 가능하다." << endl;
                gui.gotoxy(x, (y += 2));
                cout << "5개의 광물을 5개씩 전부 모아야 게임을 완료할 수 있다." << endl;

                getInput();


                //게임2 (광산게임)
                //<게임 2, 5 브금>
                system("cls");
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game2_5_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);
                this->level = 1;
                //flag = play(1);
                money();
                flag = play(1);

                if (flag) {
                    //<리얼 oh 브금>
                    system("cls");
                    gui.SetColor(WHITE);
                    money();
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("real oh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    x = 17;
                    y = 9;
                    gui.gotoxy(x, y);
                    cout << "광부가 제시한 조건을 충족시켜 사장은 급여를 받고 아르바이트를 마칠 수 있었다.";
                    gui.gotoxy(x, (y += 2));
                    cout << "그때 광부가 광산에서 많이 사용되는 폭탄이 유용할 것이라고 하며 폭탄을 사장에게 주었다.";
                    gui.SetColor(GREEN);
                    gui.gotoxy(x, (y += 2));
                    cout << "폭탄 아이템 : 랜덤한 위치에서 4*4 크기의 블록을 소멸시킨다.";

                    //폭탄 아이템 쓸 경우 ===> 폭탄 아이템 1 효과음, 폭탄 효과음 2, 요리왕 oh
                    gui.gotoxy(x, (y += 2));
                    cout << "광산에서 번 돈으로 사장은 직원의 연수비를 대준다," << endl;
                    save = 2;

                } else {
                    //<GG 효과음, 괴물쥐 효과음, 조커 브금>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gameover();
                    system("cls");
                    gui.SetColor(WHITE);
                    gui.gotoxy(28, 12);
                    cout << "한 기업의 사장이 되어 이런 일도 해결하지 못하다니,,";
                    gui.gotoxy(28, 14);
                    cout << "파산. 다시 시도해보겠습니까?(y/n)";
                    char t = getchar();
                    while (getchar() != '\n');
                    system("cls");

                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }

                getInput();
                // Clear CMD
                system("cls");
            }

            if (save <= 2) {
                x = 10;
                y = 9;
                money();
                gui.gotoxy(x, y);
                cout << "연수를 갔다온 직원은 코드 수정 작업에 큰 도움을 주었고, 행운의 아이템을 개발해내었다" << endl;
                gui.SetColor(GREEN);
                gui.gotoxy(x, (y += 2));
                cout << "행운의 아이템 : 랜덤한 위치에 4*4 배열을 생성한다. 이 아이템이 당신에게 행운이 될 지는 아무도 모릅니다." << endl;
                gui.SetColor(WHITE);
                gui.gotoxy(x, (y += 2));
                cout << "직원들은 계속하여 코드를 수정해나가며 게임을 실행해본다." << endl;

                getInput();

                // Clear CMD
                system("cls");

                //행운의 아이템 쓸 경우 ===> 함정카드 브금

                //게임3 (자음,모음)
                //<게임 3,6 브금>
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game3_6_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);

                this->level = 2;
                //flag = play(2);
                money();
                flag = play(2);

                if (flag) {
                    //<리얼 oh브금>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("real oh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    system("cls");
                    gui.SetColor(WHITE);
                    money();
                    x = 17;
                    y = 12;
                    gui.gotoxy(x, y);
                    cout << "혼란스러운 코드 속에서도 게임을 완성하여 직원은 잠시나마 안도하였다.";
                    gui.gotoxy(x, (y += 2));
                    cout << "하지만 계속하여 수정한 코드에서 자음 모음 블록이 나오자 직원들은 혼란에 빠진다.";
                    save = 3;
                } else {
                    //<GG 효과음, 괴물쥐 효과음, 조커 브금>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gameover();
                    system("cls");

                    gui.SetColor(WHITE);
                    gui.gotoxy(28, 12);
                    cout << "자신의 코드를 끝까지 플레이하지 못하다니,,,," << endl;
                    gui.gotoxy(28, 14);
                    cout << "파산. 다시 시도해보겠습니까?(y/n)";
                    char t = getchar();
                    while (getchar() != '\n');
                    system("cls");

                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }
                getInput();

                // Clear CMD
                system("cls");
            }

            if (save <= 3) {
                x = 17;
                y = 10;
                money();
                gui.gotoxy(x, y);
                cout << "그러던 중 사장이 과로로 인해 쓰러져 병원에 실려가게 된다.";
                gui.gotoxy(x, (y += 2));
                cout << "회사의 흥망을 떠나 사장이 있어야 하기에 사장을 살려야한다";
                gui.gotoxy(x, (y += 2));
                cout << "게임을 통해 사장의 건강을 차곡차곡 빈틈없이 채워넣어야 한다.";

                getInput();

                system("cls");
                x = 17;
                y = 9;
                money();
                gui.SetColor(RED);
                gui.gotoxy(x, y);
                cout << "테트리스를 차곡차곡 쌓는 형식으로" << endl;
                gui.gotoxy(x, (y += 2));
                cout << "외벽에 다른색으로 칠해진 상한선까지 모두 채워질때까지 게임이 진행된다." << endl;
                gui.gotoxy(x, (y += 2));
                cout << "전부 채운 후, 빈칸의 수가 일정 수 이하이면 게임을 클리어하게 된다." << endl;

                getInput();

                system("cls");


                //게임4 (센트롬)
                //<게임4 브금>
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game4_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);

                this->level = 3;
                money();
                flag = play(3);

                if (flag) {
                    //<리얼 oh 브금>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("real oh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    system("cls");
                    gui.SetColor(WHITE);
                    money();
                    x = 17;
                    y = 13;
                    gui.gotoxy(x, y);
                    cout << "사장은 끝내 살아났고, 이는 회사 내의 분위기를 올려 작업 속도를 더 빠르게 해주었다. ";
                    gv.setScore(gv.getScore() + 3000);
                    save = 4;
                } else {
                    //<GG 효과음, 괴물쥐 효과음, 조커 브금>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gameover();
                    system("cls");
                    gui.SetColor(WHITE);
                    gui.gotoxy(28, 12);
                    cout << "사장은 그렇게 돌아오지 못할 여행을 떠났습니다.";
                    gui.gotoxy(28, 14);
                    cout << "파산. 다시 시도해보겠습니까?(y/n)";
                    char t = getchar();
                    while (getchar() != '\n');
                    system("cls");

                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }
                getInput();
                system("cls");
            }

            x = 17;
            y = 6;
            money();
            gui.gotoxy(x, y);
            cout << "하지만 이 이상의 발전이 없는 코드를 보고 회사는 좌절에 빠진다.";
            gui.gotoxy(x, (y += 2));
            cout << "이때, 건국대학교 소프트웨어학과의 참스승인 J교수님이 ";
            gui.gotoxy(x, (y += 2));
            cout << "사장이 병원으로 실려간 소식을 들으며 Green Company의 상황을 알게 되었다. ";
            gui.gotoxy(x, (y += 2));
            cout << "이에 J교수님은 토요일 9시 20분 C++ 수업을 들어보라고 권유하였다. ";
            gui.gotoxy(x, (y += 2));
            cout << "사장과 직원들은 그 수업을 듣고 코드의 문제점을 파악하게 되고, ";
            gui.gotoxy(x, (y += 2));
            cout << "추가적으로 마지막 아이템 코드 또한 개발할 수 있게 되었다.";
            gui.SetColor(GREEN);
            gui.gotoxy(x, (y += 2));
            cout << "타노스 아이템 : 전체 블록 크기의 절반에 있는 블록들을 소멸시킨다";

            getInput();

            system("cls");

            //타노스 아이템 쓸 경우 ===> 한발 브금, legend never die 브금

            //<기합 브금>
            PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
            PlaySound(TEXT("Joker.wav"), NULL, SND_FILENAME | SND_ASYNC);

            x = 17;
            y = 10;
            money();
            gui.SetColor(GREEN);
            gui.gotoxy(x, y);
            cout << "이제 완성된 코드를 실행하여 플레이만 하면 된다. 이때까지 모아온 아이템들을 잘 사용해야 한다.";
            gui.gotoxy(x, (y += 2));
            cout << "아이템을 한번 사용할때마다 그마다의 사용료를 지불해야한다. " << endl;
            gui.gotoxy(x, (y += 2));
            cout << "게임을 완료하기 위해선 이때까지 모아온 돈을 효율적으로 사용해야 한다." << endl;
            gui.gotoxy(x, (y += 2));
            cout << "게임 완성이 눈 앞에 다가왔다. ";

            getInput();

            system("cls");


            x = 10;
            y = 8;
            money();
            gui.SetColor(GREEN);  //수정된 것
            gui.gotoxy(x, y);
            cout << "폭탄 아이템 : 랜덤한 위치에서 4*4 크기의 블록을 소멸시킨다.";
            gui.SetColor(WHITE);
            gui.gotoxy(x, (y += 2));
            cout << "U 키를 눌러 사용하고 사용할 시 2000원이 차감된다." << endl;
            gui.SetColor(GREEN);
            gui.gotoxy(x, (y += 2));
            cout << "행운의 아이템 : 랜덤한 위치에 4*4 배열을 생성한다. 이 아이템이 당신에게 행운이 될 지는 아무도 모릅니다. " << endl;
            gui.SetColor(WHITE);
            gui.gotoxy(x, (y += 2));
            cout << "I 키를 눌러 사용하고 사용할 시 1000원이 차감된다." << endl;
            gui.SetColor(GREEN);
            gui.gotoxy(x, (y += 2));
            cout << "타노스 아이템 : 전체 블록 크기의 절반에 있는 블록들을 소멸시킨다" << endl;
            gui.SetColor(WHITE);
            gui.gotoxy(x, (y += 2));
            cout << "O 키를 눌러 사용하고 사용할 시 10000원이 차감된다." << endl;
            getInput();
            system("cls");


            if (save <= 4) {
                //게임 5
    //<게임 2,5 브금>
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game2_5_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);

                this->level = 5;
                money();
                flag = play(5);


                if (flag) {
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("LGND.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    gui.SetColor(WHITE);
                    system("cls");
                    x = 17;
                    y = 9;
                    gui.gotoxy(x, y);
                    cout << "많은 버그들을 수정하여 끝내 코드를 완성하여 클리어해냈다.";
                    gui.gotoxy(x, (y += 2));
                    cout << "이 게임은 곧 테트리스 부동의 1위 게임으로 자리잡았고, ";
                    gui.gotoxy(x, (y += 2));
                    cout << "자금이 부족했던 기업은 곧 엄청난 자본을 가지게 되었다.";
                    gui.gotoxy(x, (y += 2));
                    cout << "사장은 먼저 코드를 훔쳐간 경쟁사를 소송하였고, ";
                    gui.gotoxy(x, (y += 2));
                    cout << "사용자들을 즐겁게 할 게임들을 계속하여 만들어갈 계획을 세운다.";

                    save = 4;

                    getInput();

                    system("cls");

                } else {
                    gui.show_gameover();
                    system("cls");
                    x = 28;
                    y = 13;
                    gui.gotoxy(x, y);
                    cout << "눈 앞의 기회를 놓치고 말았다. 안타까운 상황이지만, 실력을 높이고 다시 시도해보자.(y/n)" << endl;
                    //Sleep(1000);
                    //getch();
                    char t = getchar();
                    system("cls");
                    while (getchar() != '\n');
                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }
            }

            if (level == 5) {
                //엔딩 크레딧
                break;
            }
        }
    }
};