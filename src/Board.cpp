#include "Board.h"
#include "Item.h"
#include "Move.h"

using namespace std;

Board::Board() {}

Board::~Board() {}

void Board::Reset() {
    reset();
}

void Board::Info(string & in) {
    info(in);
}

void Board::GetMoves(int round, vector<unique_ptr<Move>> & moves) {
    getMoves(round, moves);
} 



//  XQBoard  //

XQBoard::XQBoard() : Board{} {
    pair<int,int> setPieceos{-1,-1};
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
            pieces[i][j] = make_unique<Bing>(i);
        }
    }
}


void XQBoard::reset() {
    int w = width();
    int h = height();
    for (int y = 0; y < h; y += 1) {
        for (int x = 0; x < w; x += 1) {
            set(x, y, nullptr);
        }
    }

    // initializes pieces and puts them into the board
    for (int i = 0; i <= 1; i += 1) {
        int y = 9*i;            // first row
        setPiece(4, y, pieces[i][0].get());
        setPiece(3, y, pieces[i][1].get());
        setPiece(5, y, pieces[i][2].get());
        setPiece(0, y, pieces[i][3].get());
        setPiece(8, y, pieces[i][4].get());
        setPiece(1, y, pieces[i][7].get());
        setPiece(7, y, pieces[i][8].get());
        setPiece(2, y, pieces[i][9].get());
        setPiece(6, y, pieces[i][10].get());
        
        y = 2 + 5*i;            // thrid row
        setPiece(1, y, pieces[i][5].get());
        setPiece(7, y, pieces[i][6].get());
        
        y = 3 + 3*i;            // fourth row
        for (int x = 0; x <= 8; x += 2) {
            setPiece(x, y, pieces[i][11+x/2].get());
        }
    }
}

void XQBoard::getMoves(int round, vector<unique_ptr<Move>> & moves)  {
    // TODO
}

void XQBoard::info(string & in) {
    int w = width();
    int h = height();
    in.reserve((2*w+3)*(h+1));
    for (int y = h-1; y >= 0; y -= 1) {
        in += y+'0';
        in += ' ';
        for (int x = 0; x < w; x += 1) {
            in += board[y][x] ? board[y][x]->Rep() : '-';
            in += ' ';
        }
        in += '\n';
    }
    in += "  ";
    for (int x = 0; x < w; x += 1) {
        in += char(x+'a');
        in += ' ';
    }
}

void XQBoard::setPiece(int x, int y, XQPiece * p) {
    p->Init(x, y);
    set(x, y, p);
}

void XQBoard::set(int x, int y, XQPiece * p) {
    board[y][x] = p;
}

void XQBoard::set(const pair<int,int> & pos, XQPiece * p) {
    set(pos.first, pos.second, p);
}

const XQPiece & XQBoard::get(int x, int y) const {
    return *board[y][x];
}

const XQPiece & XQBoard::get(const pair<int, int> & pos) const {
    return get(pos.first, pos.second);
}

int XQBoard::width() {
    return 9;
}

int XQBoard::height() {
    return 10;
}

int XQBoard::pMoveIdx(int round) {
    return round%2;
}



