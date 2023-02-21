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

double Move::Outcome() const {
    return outcome();
}

vector<Item *> Move::Items() const {
    return items();
}


//   XQMove   //
XQMove::XQMove(const pair<int, int> & from, const pair<int, int> & to, XQPiece * piece, XQPiece * target) : from{from}, to{to}, piece{piece}, target{target} {}


void XQMove::proc() {
    piece->SetPos(to);
    if (target) {
        target->SetStatus(0);
    }
}

void XQMove::undo() {
    piece->SetPos(from);
    if (target) {
        target->SetStatus(1);
    }
}

void XQMove::set(Board * board) {
    board->Set(from, nullptr);
    board->Set(to, piece);
}

void XQMove::rSet(Board * board) {
    board->Set(to, target);
    board->Set(from, piece);
}

string XQMove::rep() {
    return string{char(from.first+'a'), char(from.second + '0'), char(to.first+'a'), char(to.second+'0')};
}

unique_ptr<Move> XQMove::copy() const {
    return make_unique<XQMove>(*this);
}

double XQMove::outcome() const {
    int res = (double)piece->Val(to) -  piece->Val(from);
    if (target) {
        res += (double)target->Val(to);
    }
    return res;
}

std::vector<Item *> XQMove::items() const {
    return vector<Item *> {piece, target};
}
