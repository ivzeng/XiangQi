#include "Item.h"
#include "Board.h"
#include "Move.h"
#include "helpers.h"

using namespace std;

Item::Item() {}

Item::~Item() {}

double Item::Val() const {
    return val();
}

double Item::Val(const pair<int,int> & at) const {
    return val(at);
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

double XQPiece::val() const {
    return val(pos);
}

double XQPiece::val(const pair<int,int> & at) const {
    switch (type)
    {
    case XQPIECE_Jiang:
        return 200;
    case XQPIECE_Shi:
        return 30 + (at.second == 1-colour*6 ? 1 : 0);
    case XQPIECE_Ju:
        return 120 + (1-at.first%2)*15;
    case XQPIECE_Pao:
        return 100 + (at.first%2)*15;
    case XQPIECE_Ma:
        return 80 + (at.first%2)*10;
    case XQPIECE_Xiang:
        return 50;
    case XQPIECE_Bing:
        return 20;
    default:
        return 0;
    }
}

bool XQPiece::valid() const {
    return status;
}

