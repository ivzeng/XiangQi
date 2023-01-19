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

double Player::EOutcome(int l, priority_queue<double> & outcomes) const {
    double res = 0;
    int factor = 1;
    while (outcomes.size() != 1 && l != 1) {
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
    if (moves.size() == 0) {
        return -1000;
    }
    priority_queue<double> scores {};
    if (depth <= 0) {
        for (const unique_ptr<Move> & move :moves) {
            scores.push(move->Val());
        }
    }
    else {
        for (const unique_ptr<Move> & move :moves) {
            move->Proc();
            move->Set(board);
            scores.push(-dfsMoveAnalysis(board, move->Val(), round+1, depth-1));
            move->Undo();
            move->RSet(board);
        }
    }
    return EOutcome(15, scores) - score;
}

Move * Player::dfsMoveSearch(const vector<unique_ptr<Move>> & moves, Board * board, int round, int depth) const {
    if (moves.size() == 0) {
        return nullptr;
    }
    double minSc = 1000;
    int minIdx = 0;
    for (int i = moves.size()-1; i >= 0; i -= 1) {
        moves[i]->Proc();
        moves[i]->Set(board);
        double curSc = dfsMoveAnalysis(board, moves[0]->Val(), round+1, depth);
        if (curSc <= minSc) {
            minSc = curSc;
            minIdx = i;
        }
        //cout << moves[i]->Rep() << ' ' << minSc << endl;
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
        return dfsMoveSearch(moves, board, round, 2);
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
    return dfsMoveSearch(moves, board, round, 0);
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
    return dfsMoveSearch(moves, board, round, 2);
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
    
    default:
        return nullptr;
    }
}