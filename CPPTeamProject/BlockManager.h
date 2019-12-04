#pragma once
#include <Windows.h>
#include <time.h>
#include <iostream>
using namespace std;


class BlockManager {
private:
    /**
     * 7-shape, 4 rotation(by 91 deg), 4 * 4 matrix of data.
     */
    char block[7][4][4][4] = {

        //막대모양
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

        //네모모양
        1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

        //'ㅓ' 모양
        0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

        //'ㄱ'모양
        1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

        //'ㄴ' 모양
        1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

        //'Z' 모양
        1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

        //'S' 모양
        0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

    };

    char firstbock[7][4][4][4] = {

        //모스부호 ㅡ
        1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0,		1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0,		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

        //모스부호 .
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,


        //모스부호 ㅡ
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

        //모스부호 .
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,


        //모스부호 ㅡ
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

        //모스부호 .
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,


        //모스부호 ㅡ
        1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0,		1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0,		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

    };

    char secondblock[7][4][5][5] = {
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        0, 0, 0, 1, 0,

        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,

        1, 0, 0, 0, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,

        1, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0,

        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,

        1, 1, 1, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,

        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,

        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,

        1, 1, 1, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 1, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,

        1, 1, 1, 1, 1,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 1, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,

        1, 1, 1, 1, 1,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,

        0, 0, 0, 0, 1,
        1, 1, 1, 0, 1,
        0, 1, 0, 1, 1,
        0, 1, 0, 0, 1,
        0, 0, 0, 0, 1,

        0, 0, 0, 1, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1,

        0, 0, 0, 0, 1,
        0, 1, 0, 0, 1,
        0, 1, 0, 1, 1,
        1, 1, 1, 0, 1,
        0, 0, 0, 0, 1,

        0, 1, 0, 0, 0,
        0, 1, 1, 1, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1,
    };

    char thirdblock[7][4][5][5] = {
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,

        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,

        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,

        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,

        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,

        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        0, 0, 1, 0, 1,
        0, 0, 1, 0, 1,
        0, 0, 1, 0, 1,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,

        1, 1, 1, 1, 1,
        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        0, 1, 0, 1, 0,
        0, 1, 0, 1, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,

        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 1, 0,

        1, 1, 1, 1, 1,
        0, 1, 0, 1, 0,
        0, 1, 0, 1, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,

        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 1, 0,

        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,

        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 1, 1, 1, 1,

        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,

        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 1, 0, 0,
        1, 1, 1, 1, 1,

    };



    
public:

    void setColor(const int& shape, const int& angle) {

        int color;
        for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
                if (block[shape][angle][k][j] == 1) {
                    color = rand() % 5 + 11;
                    block[shape][angle][k][j] = color;
                }
            }
        }
    }

    const char(*getBlock())[4][4][4]; // 1,3,5

    const char(*getFirstBlock())[4][4][4]; // 0 

    const char(*getSecondBlock())[4][5][5]; // 2 

    const char(*getThirdBlock())[4][5][5]; // 4


};
