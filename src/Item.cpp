#include "Item.h"
#include "Board.h"
#include "Move.h"
#include "helpers.h"

#include <cmath>
#include <iostream>

using namespace std;

Item::Item() {}

Item::~Item() {}

double Item::Val() const {
    return val();
}

double Item::Weight() const {
    return weight();
}

bool Item::Valid() const {
    return valid();
}

char Item::ToChar() const {
    return toChar();
}

//  XiangQi Pieces  //

bool XQPiece::bonusInited = false;

double XQPiece::bonus[9][10][7]{0};

XQPiece::XQPiece() : Item{}, type{0}, status{0}, colour{-1}, pos{-1,-1} {
    initBonus();
}

XQPiece::~XQPiece() {}


void XQPiece::Init(int t, int col, int x, int y) {
    setType(t);
    setCol(col);
    SetPos(x, y);
    SetStatus();
}

void XQPiece::Init(int t, int col, const pair<int,int> & pos) {
    Init(t, col, pos.first, pos.second);
}

int XQPiece::Type() const {
    return type;
}
const pair<int, int> & XQPiece::GetPos() const {
    return pos;
}
int XQPiece::GetCol() const {
    return colour;
}

void XQPiece::setType(int t) {
    type = t;
}

void XQPiece::setCol(int col) {
    colour = col;
}

void XQPiece::SetStatus(int stat) {
    status = stat;
}

void XQPiece::SetPos(int x, int y){
    pos.first = x;
    pos.second = y;
}

void XQPiece::SetPos(const pair<int,int> & pos) {
    SetPos(pos.first, pos.second);
}

double XQPiece::weight() const {
    switch (type)
    {
    case XQPIECE_Jiang:
        return -1;
    case XQPIECE_Ju:
        return 2;
    case XQPIECE_Pao:
        return 1;
    case XQPIECE_Ma:
        return 4;
    case XQPIECE_Bing:
        return 8;
    default:
        return 0;
    }
}

double XQPiece::val() const {
    int v = 0;
    switch (type)
    {
    case XQPIECE_Jiang:
        v = 0;
    case XQPIECE_Shi:
        v = 50;
    case XQPIECE_Ju:
        v = 120;
    case XQPIECE_Pao:
        v = 100;
    case XQPIECE_Ma:
        v = 80;
    case XQPIECE_Xiang:
        v = 50;
    case XQPIECE_Bing:
        v = 20;
    }
    return v + bonus[pos.first][colour == 0 ? pos.second : 9 - pos.second][type-1];
}

bool XQPiece::valid() const {
    return status;
}

char XQPiece::toChar() const {
    if (!valid()) {
        return 1;
    }
    int x = pos.first;
    int y = pos.second;
    if (colour == 1) {
        y = 9 - y;
    }
    return x*10 + y + 2;
}

void XQPiece::initBonus() {
    if (bonusInited) {
        return;
    }
    bonusInited = true;

    for (int x : {1, 3, 5, 7}) {
        for (int y = 0; y <= 9; y += 1) {
            bonus[x][y][XQPIECE_Ju-1] = 8; 
        }
    }
    for (int y : {1, 4, 5, 8}) {
        for (int x = 0; x <= 8; x += 1) {
            bonus[x][y][XQPIECE_Ju-1] += 8; 
        }
    }

    for (int x : {0, 2, 4, 6, 8}) {
        for (int y = 0; y <= 9; y += 1) {
            bonus[x][y][XQPIECE_Pao-1] = 6-abs(x-4)*3/2; 
        }
    }
    for (int y : {2, 4, 8, 9}) {
        for (int x = 0; x <= 8; x += 1) {
            bonus[x][y][XQPIECE_Pao-1] += 10 - abs(y-5); 
        }
    }
    for (int y : {3, 5}) {
        for (int x = 0; x <= 8; x += 1) {
            bonus[x][y][XQPIECE_Pao-1] -= y; 
        }
    }

    for (int x = 2; x <= 6; x += 1) {
        for (int y = 2; y <= 8; y += 1) {
            bonus[x][y][XQPIECE_Ma-1] += 10 + y/3;
        }
    }
    for (int x : {1, 3, 5, 7}) {
        for (int y = 0; y <= 7; y += 1) {
            bonus[x][y][XQPIECE_Ma-1] += 2;
        }
    }
    for (int y : {4, 7}) {
        for (int x = 0; x <= 8; x += 1) {
            bonus[x][y][XQPIECE_Ma-1] += 3;
        }
    }

    for (int x = 0; x <= 8; x += 1) {
        for (int y = 0; y <= 9; y += 1) {
            bonus[x][y][XQPIECE_Bing-1] = 20 - pow(y-7,2) - pow(x-4,2)/2;
        }
    }

    #ifdef DEBUG
    for (int type = 0; type <= 6; type += 1) {
        cout << "type: " << type << endl;
        for (int y = 9; y >= 0; y -= 1){
            cout << y << "    ";
            for (int x = 0; x <= 8; x += 1) {
                cout << bonus[x][y][type] << ' ';
            }
            cout << endl;
        }
    }
    #endif

}

    

