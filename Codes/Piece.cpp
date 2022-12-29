#include "Piece.h"

using namespace std;

Piece::Piece(int colour, const pair<int,int> & pos) : status {1}, colour{colour}, pos{pos} {}

Jiang::Jiang(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Shi::Shi(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Ju::Ju(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Pao::Pao(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Ma::Ma(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Xiang::Xiang(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Bing::Bing(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}


void Piece::setStatus() {
    status = 1-status;
}

int Piece::value() {
    return val();
}

int Jiang::val() { return 100; }

int Shi::val() { return 20; }

int Ju::val() { return 80; }

int Pao::val() { return 60; }

int Ma::val() { return 40; }

int Xiang::val() { return 30; }

int Bing::val() { return 10; }




