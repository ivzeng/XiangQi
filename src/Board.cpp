#include "Board.h"
#include "Item.h"
#include "Move.h"
#include "Texts.h"
#include <iostream>

using namespace std;

Board::Board() {}

Board::~Board() {}

void Board::Reset() {
    reset();
}

void Board::Set(const std::pair<int, int> & pos, Item * p) {
    set(pos, p);
}

void Board::Info(string & in, const Msg & msg) {
    info(in, msg);
}

void Board::GetMoves(int round, vector<unique_ptr<Move>> & moves) {
    getMoves(round, moves);
} 



//  XQBoard  //

XQBoard::XQBoard() : Board{}, board{}, pieces{} {
    for (int col = 0; col <= 1; col += 1) {
        for (int i = 0; i <= 15; i += 1) {
            pieces[col][i] = make_unique<XQPiece>();
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
        setPiece(1, i, 4, y, pieces[i][0].get());
        setPiece(2, i, 3, y, pieces[i][1].get());
        setPiece(2, i, 5, y, pieces[i][2].get());
        setPiece(3, i, 0, y, pieces[i][3].get());
        setPiece(3, i, 8, y, pieces[i][4].get());
        setPiece(5, i, 1, y, pieces[i][7].get());
        setPiece(5, i, 7, y, pieces[i][8].get());
        setPiece(6, i, 2, y, pieces[i][9].get());
        setPiece(6, i, 6, y, pieces[i][10].get());
        
        y = 2 + 5*i;            // thrid row
        setPiece(4, i, 1, y, pieces[i][5].get());
        setPiece(4, i, 7, y, pieces[i][6].get());
        
        y = 3 + 3*i;            // fourth row
        for (int x = 0; x <= 8; x += 2) {
            setPiece(7 , i, x, y, pieces[i][11+x/2].get());
        }
    }
}


void XQBoard::info(string & m, const Msg & msg) {
    int w = width();
    int h = height();
    int vg = msg.Get(MTYPE_Board, 0, 0).size();
    const string & resetBG =msg.GetD(MTYPE_Board, 3);
    const string & setBG = msg.GetD(MTYPE_Board, 2);
    const string & setTxB = msg.GetD(MTYPE_Board, 1);
    const string & setTxR = msg.GetD(MTYPE_Board, 0);
    const string & hl = msg.Get(MTYPE_Board, 0, 1);

    string spcBk = string(msg.Get(MTYPE_Board, 1, 0).size()/3 , ' ');
    string spcSk = string(hl.size()/3, ' ') + spcBk;

    for (int y = h-1;; y -= 1) {
        m += y+'0';
        m += ' ';
        m += setBG;
        m += setTxB;
        for (int x = 0; x < w; x += 1) {
            XQPiece * p = board[y][x];
            if (p) {
                if (p->GetCol() == 0) {
                    m += setTxR;
                    m += msg.Get(MTYPE_Board, 1, p->Type()-1);
                    m += setTxB;
                }
                else {
                    m += msg.Get(MTYPE_Board, 2, p->Type()-1);
                }
            }
            else {
                m += msg.Get(MTYPE_Board, 0, edgeType(x, y));
            }
            if (x != w-1) {
                m += hl;
            }
            else {
                m += spcBk;
            }
        }
        m += resetBG;
        m += '\n';
        if (y == 0) {
            break;
        }
        const string vl = y == 5 ? " " : msg.Get(MTYPE_Board, 0, 2);

        for (int i = vg; i > 0; i -= 1) {
            m += "  ";
            m += setBG;
            m += setTxB;
            m += ' ';
            m += vl;
            for (int j = width()-1; j > 0; j -= 1) {
                m += spcSk;
                m += vl;
            }
            m += spcBk;
            m += resetBG;
            m += '\n';
        }
    }
    m += spcSk;
    for (int x = 0; x < w; x += 1) {
        m += char(x+'a');
        m += spcSk;
    }
}

void XQBoard::setPiece(int type, int col, int x, int y, XQPiece * p) {
    p->Init(type, col, x, y);
    set(x, y, p);
}

void XQBoard::set(int x, int y, XQPiece * p) {
    board[y][x] = p;
}

void XQBoard::set(const pair<int,int> & pos, Item * p) {
    XQPiece * xqp = dynamic_cast<XQPiece *>(p);
    set(pos.first, pos.second, xqp);
}

XQPiece * XQBoard::get(int x, int y) {
    return board[y][x];
}

XQPiece * XQBoard::get(const pair<int, int> & pos) {
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

int XQBoard::edgeType(int x, int y) {
    const int h = height()-1;
    const int w = width()-1;
    if (x == 0) {
        if (y == 0) { return 5; }
        if (y == h) { return 3; }
        return 7;
    }
    if (x == w) {
        if (y == 0) { return 6; }
        if (y == h) { return 4; }
        return 8;
    }
    if (y == 0 || y == h/2+1) {
        return 10;
    }
    if (y == h || y == h/2) {
        return 9;
    }
    return 11;
}


void XQBoard::getMoves(int round, vector<unique_ptr<Move>> & moves)  {
    int col = pMoveIdx(round);
    for (const unique_ptr<XQPiece> & p : pieces[col]) {
        if (p->Valid()) { 
            scan(moves, *p);
        }
    }
}

void XQBoard::scan(vector<unique_ptr<Move>> & moves, const XQPiece & p) {
    switch (p.Type())
    {
    case 1:
        jScan(moves, p.GetPos(), p.GetCol());
        break;
    case 2:
        sScan(moves, p.GetPos(), p.GetCol());
        break;
    case 3:
        lScan(moves, p.GetPos(), p.GetCol());
        break;
    case 4:
        lScan(moves, p.GetPos(), p.GetCol(), 1);
        break;
    case 5:
        mScan(moves, p.GetPos(), p.GetCol());
        break;
    case 6:
        xScan(moves, p.GetPos(), p.GetCol());
        break;
    case 7:
        bScan(moves, p.GetPos(), p.GetCol());
        break;
    default:
        break;
    }
}

void XQBoard::jScan(vector<unique_ptr<Move>> & moves, const pair<int,int> & pos, int col) {
    int ub = 2 + col*7;
    int lb = 0 + col*7;
    pair<int, int> to {pos};
    if(++to.first <= 5) {
        insertMove(moves, pos, to, col, true);
    }
    to.first = pos.first-1;
    if(to.first >= 3) {
        insertMove(moves, pos, to, col, true);
    }
    to.first = pos.first;
    to.second = pos.second+1;
    if(to.second <= ub) {
        insertMove(moves, pos, to, col, true);
    }
    to.second = pos.second-1;
    if(to.second >= lb) {
        insertMove(moves, pos, to, col, true);
    }
}

void XQBoard::sScan(vector<unique_ptr<Move>> & moves, const pair<int,int> & pos, int col) {
    if (pos.first == 4) {
        insertMove(moves, pos, {pos.first-1, pos.second-1}, col);
        insertMove(moves, pos, {pos.first+1, pos.second-1}, col);
        insertMove(moves, pos, {pos.first-1, pos.second+1}, col);
        insertMove(moves, pos, {pos.first+1, pos.second+1}, col);
    }
    else {
        insertMove(moves, pos, {4, 1+col*7}, col);
    }
}

void XQBoard::lScan(vector<unique_ptr<Move>> & moves, const pair<int,int> & pos, int col, int skip) {
    int w = width();
    int h = height();
    pair<int,int>to{pos};
    to.first += 1;
    for (int pass = 0; to.first < w && lInsertMove(moves, pos, to, col, pass, skip); to.first += 1);
    to.first = pos.first-1;
    for (int pass = 0; to.first >= 0 && lInsertMove(moves, pos, to, col, pass, skip); to.first -= 1);
    to.first = pos.first;
    to.second = pos.second+1;
    for (int pass = 0; to.second < h && lInsertMove(moves, pos, to, col, pass, skip); to.second += 1);
    to.second = pos.second-1;
    for (int pass = 0; to.second >= 0 && lInsertMove(moves, pos, to, col, pass, skip); to.second -= 1);
}

void XQBoard::mScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col) {
    int w = width();
    int h = height();
    if (pos.first + 2 < w && !get(pos.first+1, pos.second)) {
        if (pos.second + 1 < h) {
            insertMove(moves, pos, {pos.first+2, pos.second+1}, col);
        }
        if (pos.second - 1 >= 0) {
            insertMove(moves, pos, {pos.first+2, pos.second-1}, col);
        }
    }
    if (pos.first - 2 >= 0 && !get(pos.first-1, pos.second)) {
        if (pos.second + 1 < h) {
            insertMove(moves, pos, {pos.first-2, pos.second+1}, col);
        }
        if (pos.second - 1 >= 0) {
            insertMove(moves, pos, {pos.first-2, pos.second-1}, col);
        }
    }
    if (pos.second + 2 < h && !get(pos.first, pos.second+1)) {
        if (pos.first + 1 < w) {
            insertMove(moves, pos, {pos.first+1, pos.second+2}, col);
        }
        if (pos.first - 1 >= 0) {
            insertMove(moves, pos, {pos.first-1, pos.second+2}, col);
        }
    }
    if (pos.second - 2 >= 0 && !get(pos.first, pos.second-1)) {
        if (pos.first + 1 < w) {
            insertMove(moves, pos, {pos.first+1, pos.second-2}, col);
        }
        if (pos.first - 1 >= 0) {
            insertMove(moves, pos, {pos.first-1, pos.second-2}, col);
        }
    }
}

void XQBoard::xScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col) {
    int w = width();
    int h = height();
    if (pos.second+2 < h && (pos.second+2)/5 == pos.second/5) {
        if (pos.first+2 < w && !get(pos.first+1, pos.second+1)) {
            insertMove(moves, pos, {pos.first+2, pos.second+2}, col);
        }
        if (pos.first-2 >= 0 && !get(pos.first-1, pos.second+1)) {
            insertMove(moves, pos, {pos.first-2, pos.second+2}, col);
        }
    }
    if (pos.second-2 >= 0 && (pos.second-2)/5 == pos.second/5) {
        if (pos.first+2 < w && !get(pos.first+1, pos.second-1)) {
            insertMove(moves, pos, {pos.first+2, pos.second-2}, col);
        }
        if (pos.first-2 >= 0 && !get(pos.first-1, pos.second-1)) {
            insertMove(moves, pos, {pos.first-2, pos.second-2}, col);
        }
    }
}

void XQBoard::bScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col) {
    int dir = 1-col*2;
    if (pos.first + dir >= 0 && pos.second + dir < height()) {
        insertMove(moves, pos, {pos.first, pos.second+dir}, col);
    }
    if (col != pos.second/5) {
        if (pos.first+1 < width()) {
            insertMove(moves, pos, {pos.first+1, pos.second}, col);
        }
        if (pos.first-1 >= 0) {
            insertMove(moves, pos, {pos.first-1, pos.second}, col);
        }
    }
}


void XQBoard::insertMove(vector<unique_ptr<Move>> & moves, const pair<int,int> & from, const pair<int,int> & to, int col, bool isK) {
    XQPiece * target = get(from);
    XQPiece * captured = get(to);
    if (captured && captured->GetCol() == col) {
        return;
    }

    set(from, nullptr);
    set(to, target);
    if (safe(col , (isK ? to : pieces[col][0]->GetPos()))) {
        moves.emplace_back(make_unique<XQMove>(from, to, target, captured));
    }
    set(from, target);
    set(to, captured);
}

bool XQBoard::lInsertMove(vector<unique_ptr<Move>> & moves, const pair<int,int> & from, const pair<int,int> & to, int col, int & pass, int skip) {
    if(get(to)) {
            if (pass == skip) {
                insertMove(moves, from, to, col);
                return false;
            }
            pass += 1;
        }
        if (pass == 0) {
            insertMove(moves, from, to, col);
        }
        return true;
}

bool XQBoard::safe(int col, const pair<int, int> & pos) const {
    return true;
}



