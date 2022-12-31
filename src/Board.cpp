#include "Board.h"
#include "Piece.h"

using namespace std;

Board::Board() {}

Board::~Board() {}

int Board::Init() {
    return init();
}



//  XQBoard  //

XQBoard::XQBoard() : Board{} {
    pair<int,int> initPos{-1,-1};
    for (int i = 0; i <= 1; i += 1) {
        pieces[i][0] = make_unique<Jiang>(i);
        pieces[i][1] = make_unique<Shi>(i);
        pieces[i][2] = make_unique<Shi>(i);
        pieces[i][3] = make_unique<Ju>(i);
        pieces[i][4] = make_unique<Ju>(i);
        pieces[i][5] = make_unique<Pao>(i);
        pieces[i][6] = make_unique<Pao>(i);
        pieces[i][7] = make_unique<Ma>(i);
        pieces[i][8] = make_unique<Ma>(i);
        pieces[i][9] = make_unique<Xiang>(i);
        pieces[i][10] = make_unique<Xiang>(i);
        for (int j = 11; j <= 15; j += 1) {
            pieces[i][j] = make_unique<Xiang>(i);
        }
    }
}


int XQBoard::init() {
    for (int y = 0; y < 10; y += 1) {
        for (int x = 0; x < 9; x += 1) {
            set(x, y, nullptr);
        }
    }

    // initializes pieces and puts them into the board
    for (int i = 0; i <= 1; i += 1) {
        int y = 9*i;            // first row
        initP(4, y, pieces[i][0].get());
        initP(3, y, pieces[i][1].get());
        initP(5, y, pieces[i][2].get());
        initP(0, y, pieces[i][3].get());
        initP(8, y, pieces[i][4].get());
        initP(1, y, pieces[i][7].get());
        initP(7, y, pieces[i][8].get());
        initP(2, y, pieces[i][9].get());
        initP(6, y, pieces[i][10].get());
        
        y = 2 + 5*i;            // thrid row
        initP(1, y, pieces[i][5].get());
        initP(7, y, pieces[i][6].get());
        
        y = 3 + 3*i;            // fourth row
        for (int x = 0; x <= 10; x += 2) {
            initP(x, y, pieces[i][11+x/2].get());
        }
    }
}

void XQBoard::initP(int x, int y, XQPiece * p) {
    p->Init(x, y);
    set(x, y, p);
}

void XQBoard::set(int x, int y, XQPiece * p) {
    board[y][x] = p;
}

void XQBoard::set(const pair<int,int> & pos, XQPiece * p) {
    set(pos.first, pos.second, p);
}

XQPiece * XQBoard::get(int x, int y) const {
    return board[y][x];
}

XQPiece * XQBoard::get(const pair<int, int> & pos) const {
    return get(pos.first, pos.second);
}


