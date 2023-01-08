#include "Move.h"
#include "Item.h"

using namespace std;

Move::Move() {}

Move::~Move() {}

void Move::Proc() {
    proc();
}

void Move::Undo() {
    undo();
}

string Move::Rep() {
    return rep();
}

//   XQMove   //
XQMove::XQMove(const pair<int, int> & from, const pair<int, int> & to, XQPiece * target, XQPiece * captured) : from{from}, to{to}, target{target}, captured{captured} {}

int XQMove::Val() {
    return 0;
}

void XQMove::proc() {
    target->SetPos(to);
    if (captured) {
        captured->SetStatus(0);
    }
}

void XQMove::undo() {
    target->SetPos(from);
    if (captured) {
        captured->SetStatus(1);
    }
}

string XQMove::rep() {
    return "" + char(from.first+'a') + char(from.first+'0') + char(from.second+'a') + char(from.second+'0');
}

