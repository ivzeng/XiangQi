#include "Player.h"
#include "BoardGame.h"
#include "Move.h"
#include "Board.h"
#include <iostream>

using namespace std;

Player::Player() {}

Player::~Player() {}

string Player::Rep() {
    return rep();
}

Move * Player::Decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) {
    return decide(cmd, moves, board, round);
}

double Player::outcome(Board * board,  Move * move, double score, int col) const {
    return move->Val() - score;
}

double Player::eOutcome(int l, priority_queue<double> & outcomes) const {
    double res = 0;
    int factor = 1;
    if ((int)outcomes.size() < l) {
        l = outcomes.size();
    }

    while (l != 1) {
        factor *= 2;
        l -= 1;
        res +=(double)outcomes.top()/factor;
        outcomes.pop();
    }
    res += outcomes.top()/factor;
    return res;
}


double Player::dfsMoveAnalysis(Board * board, double score, int round, int depth) const {
    vector<unique_ptr<Move>> moves{};
    board->GetMoves(round, moves);
    int l = moves.size();
    if (l == 0) {
        return -1000;
    }
    for (int i : {52, 45, 31, 20, 13, 6}) {
        if (l > i) {
            depth -= 1;
        }
    }
    priority_queue<double> scores {};
    if (depth <= 0) {
        for (const unique_ptr<Move> & move :moves) {
            scores.push(outcome(board, move.get(), score, board->PMoveIdx(round)));
        }
        return eOutcome(20, scores);
    }
    for (const unique_ptr<Move> & move :moves) {
        move->Proc();
        move->Set(board);
        scores.push(-dfsMoveAnalysis(board, move->Val()-score, round+1, depth-4));
        move->Undo();
        move->RSet(board);
    }
    return eOutcome(10, scores);
}

Move * Player::dfsMoveSearch(const vector<unique_ptr<Move>> & moves, Board * board, int round, int depth) const {
    if (moves.size() == 0) {
        return nullptr;
    }
    else if (moves.size() == 1) {
        return moves[0].get();
    }
    double minSc = 1000;
    int minIdx = 0;
    for (int i = moves.size()-1; i >= 0; i -= 1) {
        moves[i]->Proc();
        moves[i]->Set(board);
        double curSc = dfsMoveAnalysis(board, moves[i]->Val(), round+1, depth);
        if (curSc <= minSc) {
            minSc = curSc;
            minIdx = i;
        }
        cout << moves[i]->Rep() << ' ' << curSc << endl;
        moves[i]->Undo();
        moves[i]->RSet(board);
    }
    return moves[minIdx].get();
}

//    Human    //
Human::Human() : Player{} {}

std::string Human::rep() {
    return "human";
}

Move * Human::decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) {
    if (cmd == "hint") {
        return dfsMoveSearch(moves, board, round, 10);
    }
    for (auto & move : moves) {
        if (move->Rep() == cmd) {
            return move.get();
        }
    }
    return nullptr;
}

// computer players //
Computer::Computer() : Player{} {}
Computer::~Computer() {}

// computer0 //
Computer0::Computer0() : Computer{} {}

string Computer0::rep() {
    return "computer0";
}

Move * Computer0::decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) {
    if (cmd != "m" && cmd != "") {
        return nullptr;
    }
    return dfsMoveSearch(moves, board, round, 6);
}


//  Computer 1  //
Computer1::Computer1() : Computer{} {}

string Computer1::rep() {
    return "computer1";
}

Move * Computer1::decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) {
    if (cmd != "m" && cmd != "") {
        return nullptr;
    }
    return dfsMoveSearch(moves, board, round, 20);
}

// computer 2   //
Computer2::Computer2() : Computer{} {} 

string Computer2::rep() {
    return "computer2";
}

Move * Computer2::decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) {
    if (cmd != "m" && cmd != "") {
        return nullptr;
    }
    return dfsMoveSearch(moves, board, round, 5);
}

double Computer2::outcome(Board * board, Move * move, double score, int col) const {
    move->Proc();
    move->Set(board);
    double res = board->Val(col);
    move->Undo();
    move->RSet(board);
    return res;
}


//  other functions   //
unique_ptr<Player> makePlayer(int type) {
    switch (type)
    {
    case 0:
        return make_unique<Human>();
    case 1:
        return make_unique<Computer0>();
    case 2:
        return make_unique<Computer1>();
    case 3:
        return make_unique<Computer2>();
    
    default:
        return nullptr;
    }
}