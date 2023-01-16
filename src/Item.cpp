#include "Item.h"
#include "Board.h"
#include "Move.h"
#include "helpers.h"

using namespace std;

Item::Item() {}

Item::~Item() {}

int Item::Val() const {
    return val();
}


bool Item::Valid() const {
    return valid();
}

//  XiangQi Pieces  //

XQPiece::XQPiece() : Item{}, type{0}, status{0}, colour{-1}, pos{-1,-1} {}


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

int XQPiece::val() const {
    switch (type)
    {
    case 1:
        return 200;
        break;
    case 2:
        return 30;
        break;
    case 3:
        return 120;
        break;
    case 4:
        return 100;
        break;
    case 5:
        return 80;
        break;
    case 6:
        return 50;
        break;
    case 7:
        return 20;
        break;
    default:
        break;
    }
    return 0;
}

bool XQPiece::valid() const {
    return status;
}

