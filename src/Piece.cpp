#include "Piece.h"
#include "helpers.h"

using namespace std;

Item::Item() {}

Item::~Item() {}

int Item::Val() const {
    return val();
}

char Item::Rep() const {
    return rep();
}

//  XiangQi Pieces  //

XQPiece::XQPiece(int colour) : Item{}, status{-1}, colour{colour}, pos{-1,-1} {}

Jiang::Jiang(int colour) : XQPiece{colour} {}

Shi::Shi(int colour) : XQPiece{colour} {}

Ju::Ju(int colour) : XQPiece{colour} {}

Pao::Pao(int colour) : XQPiece{colour} {}

Ma::Ma(int colour) : XQPiece{colour} {}

Xiang::Xiang(int colour) : XQPiece{colour} {}

Bing::Bing(int colour) : XQPiece{colour} {}


void XQPiece::Init(int x, int y) {
    setPos(x, y);
    setStatus();
}

void XQPiece::Init(const pair<int,int> & pos) {
    Init(pos.first, pos.second);
}

void XQPiece::setStatus(int stat) {
    status = stat;
}

void XQPiece::setPos(int x, int y){
    pos.first = x;
    pos.second = y;
}

void XQPiece::setPos(const pair<int,int> & pos) {
    setPos(pos.first, pos.second);
}



int Jiang::val() const  { return 100; }

int Shi::val() const    { return 20; }

int Ju::val() const     { return 80; }

int Pao::val() const    { return 60; }

int Ma::val() const     { return 40; }

int Xiang::val() const  { return 30; }

int Bing::val() const   { return 10; }


char Jiang::rep() const  { return colour ? 'j' : 'J'; }

char Shi::rep() const    { return colour ? 's' : 'S'; }

char Ju::rep() const     { return colour ? 'g' : 'G'; }

char Pao::rep() const    { return colour ? 'p' : 'P'; }

char Ma::rep() const     { return colour ? 'm' : 'M'; }

char Xiang::rep() const  { return colour ? 'x' : 'X'; }

char Bing::rep() const   { return colour ? 'b' : 'B'; }





