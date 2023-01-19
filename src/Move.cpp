#include "Move.h"
#include "Board.h"
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

void Move::Set(Board * board) {
    set(board);
}

void Move::RSet(Board * board) {
    rSet(board);
}

string Move::Rep() {
    return rep();
}

unique_ptr<Move> Move::Copy () const {
    return copy();
}

double Move::Val() const {
    return val();
}

//   XQMove   //
XQMove::XQMove(const pair<int, int> & from, const pair<int, int> & to, XQPiece * target, XQPiece * captured) : from{from}, to{to}, target{target}, captured{captured} {}


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

void XQMove::set(Board * board) {
    board->Set(from, nullptr);
    board->Set(to, target);
}

void XQMove::rSet(Board * board) {
    board->Set(to, captured);
    board->Set(from, target);
}

string XQMove::rep() {
    return string{char(from.first+'a'), char(from.second + '0'), char(to.first+'a'), char(to.second+'0')};
}

unique_ptr<Move> XQMove::copy() const {
    return make_unique<XQMove>(*this);
}

double XQMove::val() const {
    int res = target->Val(to) -  target->Val(from);
    if (captured) {
        res += captured->Val(to);
    }
    return res;
}
