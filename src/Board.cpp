#include "Board.h"
#include "Item.h"
#include "Move.h"
#include "Texts.h"
#include <iostream>
#include <algorithm>
#include <functional>

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

void Board::GetMoves(int round, vector<unique_ptr<Move>> & moves, int mode) {
    getMoves(round, moves, mode);
} 


int Board::PMoveIdx(int round) const {
    return pMoveIdx(round);
}

double Board::Outcome(int round) {
    return outcome(round);
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
        setPiece(XQPIECE_Jiang, i, 4, y, pieces[i][0].get());
        setPiece(XQPIECE_Shi, i, 3, y, pieces[i][1].get());
        setPiece(XQPIECE_Shi, i, 5, y, pieces[i][2].get());
        setPiece(XQPIECE_Ju, i, 0, y, pieces[i][3].get());
        setPiece(XQPIECE_Ju, i, 8, y, pieces[i][4].get());
        setPiece(XQPIECE_Ma, i, 1, y, pieces[i][7].get());
        setPiece(XQPIECE_Ma, i, 7, y, pieces[i][8].get());
        setPiece(XQPIECE_Xiang, i, 2, y, pieces[i][9].get());
        setPiece(XQPIECE_Xiang, i, 6, y, pieces[i][10].get());
        
        y = 2 + 5*i;            // thrid row
        setPiece(XQPIECE_Pao, i, 1, y, pieces[i][5].get());
        setPiece(XQPIECE_Pao, i, 7, y, pieces[i][6].get());
        
        y = 3 + 3*i;            // fourth row
        for (int x = 0; x <= 8; x += 2) {
            setPiece(XQPIECE_Bing , i, x, y, pieces[i][11+x/2].get());
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

XQPiece * XQBoard::get(int x, int y) const {
    return board[y][x];
}

XQPiece * XQBoard::get(const pair<int, int> & pos) const {
    return get(pos.first, pos.second);
}

int XQBoard::width() const {
    return 9;
}

int XQBoard::height() const {
    return 10;
}

int XQBoard::pMoveIdx(int round) const {
    return round%2;
}

double XQBoard::outcome(int round) {
    // gets theats moves and protections moves sorted in ascending order according to the value of the piece to move
    vector<unique_ptr<Move>> threats{};
    vector<unique_ptr<Move>> protections{};
    getMoves(round, threats, 1);
    getMoves(round+1, protections, 2);
    function<bool(const unique_ptr<Move> &, const unique_ptr<Move> & )> moves_comp ([] (const unique_ptr<Move> & m1, const unique_ptr<Move> & m2) {
        return m1->PVal() < m2->PVal();
    });
    sort(threats.begin(), threats.end(), moves_comp);
    sort(protections.begin(), protections.end(), moves_comp);
    vector<pair<int, int>> markedPoss{};
    pair<int, int> posScore[10][9] {pair<int, int>{0,0}};
    
    return 0;
}

int XQBoard::edgeType(int x, int y) const {
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


void XQBoard::getMoves(int round, vector<unique_ptr<Move>> & moves, int mode)  {
    int col = pMoveIdx(round);
    for (const unique_ptr<XQPiece> & p : pieces[col]) {
        if (p->Valid()) { 
            scan(moves, *p, mode);
        }
    }
}

void XQBoard::scan(vector<unique_ptr<Move>> & moves, const XQPiece & p, int mode) {
    switch (p.Type())
    {
    case XQPIECE_Jiang:
        jScan(moves, p.GetPos(), p.GetCol(), mode);
        break;
    case XQPIECE_Shi:
        sScan(moves, p.GetPos(), p.GetCol(), mode);
        break;
    case XQPIECE_Ju:
        lScan(moves, p.GetPos(), p.GetCol(), mode);
        break;
    case XQPIECE_Pao:
        lScan(moves, p.GetPos(), p.GetCol(), mode, 1);
        break;
    case XQPIECE_Ma:
        mScan(moves, p.GetPos(), p.GetCol(), mode);
        break;
    case XQPIECE_Xiang:
        xScan(moves, p.GetPos(), p.GetCol(), mode);
        break;
    case XQPIECE_Bing:
        bScan(moves, p.GetPos(), p.GetCol(), mode);
        break;
    default:
        break;
    }
}

void XQBoard::jScan(vector<unique_ptr<Move>> & moves, const pair<int,int> & pos, int col, int mode) {
    int ub = 2 + col*7;
    int lb = 0 + col*7;
    pair<int, int> to {pos};
    if(++to.first <= 5) {
        insertMove(moves, pos, to, col, mode, true);
    }
    to.first = pos.first-1;
    if(to.first >= 3) {
        insertMove(moves, pos, to, col, mode, true);
    }
    to.first = pos.first;
    to.second = pos.second+1;
    if(to.second <= ub) {
        insertMove(moves, pos, to, col, mode, true);
    }
    to.second = pos.second-1;
    if(to.second >= lb) {
        insertMove(moves, pos, to, col, mode, true);
    }
}

void XQBoard::sScan(vector<unique_ptr<Move>> & moves, const pair<int,int> & pos, int col, int mode) {
    if (pos.first == 4) {
        insertMove(moves, pos, {pos.first-1, pos.second-1}, col, mode);
        insertMove(moves, pos, {pos.first+1, pos.second-1}, col, mode);
        insertMove(moves, pos, {pos.first-1, pos.second+1}, col, mode);
        insertMove(moves, pos, {pos.first+1, pos.second+1}, col, mode);
    }
    else {
        insertMove(moves, pos, {4, 1+col*7}, col, mode);
    }
}

void XQBoard::lScan(vector<unique_ptr<Move>> & moves, const pair<int,int> & pos, int col, int mode, int skip) {
    int w = width();
    int h = height();
    pair<int,int>to{pos};
    to.first += 1;
    for (int pass = 0; to.first < w && lInsertMove(moves, pos, to, col, pass, mode, skip); to.first += 1);
    to.first = pos.first-1;
    for (int pass = 0; to.first >= 0 && lInsertMove(moves, pos, to, col, pass, mode, skip); to.first -= 1);
    to.first = pos.first;
    to.second = pos.second+1;
    for (int pass = 0; to.second < h && lInsertMove(moves, pos, to, col, pass, mode, skip); to.second += 1);
    to.second = pos.second-1;
    for (int pass = 0; to.second >= 0 && lInsertMove(moves, pos, to, col, pass, mode, skip); to.second -= 1);
}

void XQBoard::mScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col, int mode) {
    int w = width();
    int h = height();
    if (pos.first + 2 < w && !get(pos.first+1, pos.second)) {
        if (pos.second + 1 < h) {
            insertMove(moves, pos, {pos.first+2, pos.second+1}, col, mode);
        }
        if (pos.second - 1 >= 0) {
            insertMove(moves, pos, {pos.first+2, pos.second-1}, col, mode);
        }
    }
    if (pos.first - 2 >= 0 && !get(pos.first-1, pos.second)) {
        if (pos.second + 1 < h) {
            insertMove(moves, pos, {pos.first-2, pos.second+1}, col, mode);
        }
        if (pos.second - 1 >= 0) {
            insertMove(moves, pos, {pos.first-2, pos.second-1}, col, mode);
        }
    }
    if (pos.second + 2 < h && !get(pos.first, pos.second+1)) {
        if (pos.first + 1 < w) {
            insertMove(moves, pos, {pos.first+1, pos.second+2}, col, mode);
        }
        if (pos.first - 1 >= 0) {
            insertMove(moves, pos, {pos.first-1, pos.second+2}, col, mode);
        }
    }
    if (pos.second - 2 >= 0 && !get(pos.first, pos.second-1)) {
        if (pos.first + 1 < w) {
            insertMove(moves, pos, {pos.first+1, pos.second-2}, col, mode);
        }
        if (pos.first - 1 >= 0) {
            insertMove(moves, pos, {pos.first-1, pos.second-2}, col, mode);
        }
    }
}

void XQBoard::xScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col, int mode) {
    int w = width();
    int h = height();
    if (pos.second+2 < h && (pos.second+2)/5 == pos.second/5) {
        if (pos.first+2 < w && !get(pos.first+1, pos.second+1)) {
            insertMove(moves, pos, {pos.first+2, pos.second+2}, col, mode);
        }
        if (pos.first-2 >= 0 && !get(pos.first-1, pos.second+1)) {
            insertMove(moves, pos, {pos.first-2, pos.second+2}, col, mode);
        }
    }
    if (pos.second-2 >= 0 && (pos.second-2)/5 == pos.second/5) {
        if (pos.first+2 < w && !get(pos.first+1, pos.second-1)) {
            insertMove(moves, pos, {pos.first+2, pos.second-2}, col, mode);
        }
        if (pos.first-2 >= 0 && !get(pos.first-1, pos.second-1)) {
            insertMove(moves, pos, {pos.first-2, pos.second-2}, col, mode);
        }
    }
}

void XQBoard::bScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col, int mode) {
    int dir = 1-col*2;
    if (pos.second + dir >= 0 && pos.second + dir < height()) {
        insertMove(moves, pos, {pos.first, pos.second+dir}, col, mode);
    }
    if (col != pos.second/5) {
        if (pos.first+1 < width()) {
            insertMove(moves, pos, {pos.first+1, pos.second}, col, mode);
        }
        if (pos.first-1 >= 0) {
            insertMove(moves, pos, {pos.first-1, pos.second}, col, mode);
        }
    }
}


void XQBoard::insertMove(vector<unique_ptr<Move>> & moves, const pair<int,int> & from, const pair<int,int> & to, int col, int mode, bool isK) {
    XQPiece * piece = get(from);
    XQPiece * target = get(to);
    if (!target) {
        if (mode != 0) {
            return;
        }
    }
    else if ((target->GetCol() == col && mode != 2) || (target->GetCol() != col && mode == 2)) {
        return;
    }


    set(from, nullptr);
    set(to, piece);
    if (safe(col , (isK ? to : pieces[col][0]->GetPos()))) {
        moves.emplace_back(make_unique<XQMove>(from, to, piece, target));
    }
    set(from, piece);
    set(to, target);
}

bool XQBoard::lInsertMove(vector<unique_ptr<Move>> & moves, const pair<int,int> & from, const pair<int,int> & to, int col, int & pass, int mode, int skip) {
    if(get(to)) {
            if (pass == skip) {
                insertMove(moves, from, to, col, mode);
                return false;
            }
            pass += 1;
        }
        if (pass == 0) {
            insertMove(moves, from, to, col, mode);
        }
        return true;
}

bool XQBoard::checkLPath(int col, int & pass, XQPiece * p) const {
    if (p) {
        pass += 1;
        if (p->GetCol() == col) {
            return true;
        }
        if ((pass == 1 && (p->Type() == XQPIECE_Jiang || p->Type() == XQPIECE_Ju)) || (pass == 2 && p->Type() == XQPIECE_Pao)) {
            return false;
        }
    }
    return true;
}

bool XQBoard::safe(int col, const pair<int, int> & pos) const {
    int h = height();
    int w = width();

    // check Bing's attack
    XQPiece * p = get(pos.first, pos.second+1-col*2);
    if ((p && p->GetCol() != col && p->Type() == XQPIECE_Bing) || 
    (get(pos.first-1, pos.second) && get(pos.first-1, pos.second)->Type() == XQPIECE_Bing) || 
    (get(pos.first+1, pos.second) && get(pos.first+1, pos.second)->Type() == XQPIECE_Bing)) {
        return false;
    }

    // check lines
    for (int y = pos.second+1, pass = 0; y < h && pass <= 1; y += 1) {
        if (!checkLPath(col, pass, get(pos.first, y))) {
            return false;
        }
    }
    for (int y = pos.second-1, pass = 0; y >= 0 && pass <= 1; y -= 1) {
        if (!checkLPath(col, pass, get(pos.first, y))) {
            return false;
        }
    }
    for (int x = pos.first+1, pass = 0; x < w && pass <= 1; x += 1) {
        if (!checkLPath(col, pass, get(x, pos.second))) {
            return false;
        }
    }
    for (int x = pos.first-1, pass = 0; x >= 0 && pass <= 1; x -= 1) {
        if (!checkLPath(col, pass, get(x, pos.second))) {
            return false;
        }
    }

    // check Ma's attack
    for (int x : {-1, 1}) {
        for (int y : {-1, 1}) {
            if (pos.second+y >= 0 && pos.second+y < h && !get(pos.first+x, pos.second+y)) {
                if (pos.second+y*2 >= 0 && pos.second+y*2 < h)  {
                    XQPiece * p = get(pos.first+x, pos.second+y*2);
                    if (p && p->GetCol() != col && p->Type() == XQPIECE_Ma) {
                        return false;
                    }
                }
                XQPiece * p = get(pos.first+x*2, pos.second+y);
                if (p &&  p->GetCol() != col && p->Type() == XQPIECE_Ma) {
                    return false;
                }
            }
        }
    }
    return true;
}



