#include "Item.h"
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

XQPiece::XQPiece(int colour) : Item{}, status{0}, colour{colour}, pos{-1,-1} {}

XQPiece::~XQPiece() {}

Jiang::Jiang(int colour) : XQPiece{colour} {}

Shi::Shi(int colour) : XQPiece{colour} {}

Ju::Ju(int colour) : XQPiece{colour} {}

Pao::Pao(int colour) : XQPiece{colour} {}

Ma::Ma(int colour) : XQPiece{colour} {}

Xiang::Xiang(int colour) : XQPiece{colour} {}

Bing::Bing(int colour) : XQPiece{colour} {}


void XQPiece::Init(int x, int y) {
    SetPos(x, y);
    SetStatus();
}

void XQPiece::Init(const pair<int,int> & pos) {
    Init(pos.first, pos.second);
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





