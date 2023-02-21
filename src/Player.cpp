#include "Player.h"
#include "BoardGame.h"
#include "Move.h"
#include "Board.h"
#include "helpers.h"
#include <iostream>

using namespace std;


/**   Player   **/

Player::Player() {}

Player::~Player() {}

string Player::Rep() {
    return rep();
}

Move * Player::Decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) {
    return decide(cmd, moves, board, round);
}

double Player::outcome(Board * board, double score, int round, Move * move) const {
    return score;
}

double Player::dfsMoveAnalysis(Board * board, double score, int round, int depth) const {
    vector<unique_ptr<Move>> moves{};
    board->GetMoves(round, moves);
    int l = moves.size();
    if (l == 0) {
        return -1000;
    }
    for (int i : {52, 40, 28, 20, 13, 7}) {
        if (l > i) {
            depth -= 1;
        }
    }
    priority_queue<double> scores {};
    if (depth <= 0) {
        for (const unique_ptr<Move> & move :moves) {
            scores.push(outcome(board, move->Outcome()-score, round+1, move.get()));
        }
        return expectedOutcome(20, scores);
    }
    for (const unique_ptr<Move> & move :moves) {
        move->Proc();
        move->Set(board);
        scores.push(-dfsMoveAnalysis(board, move->Outcome()-score, round+1, depth-4));
        move->Undo();
        move->RSet(board);
    }
    return expectedOutcome(10, scores, 0.7);
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
        double curSc = dfsMoveAnalysis(board, moves[i]->Outcome(), round+1, depth);
        if (curSc <= minSc) {
            minSc = curSc;
            minIdx = i;
        }
        //cout << moves[i]->Rep() << ' ' << curSc << endl;
        moves[i]->Undo();
        moves[i]->RSet(board);
    }
    return moves[minIdx].get();
}

/**    Human    **/
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

/***  Computer Players   ***/
Computer::Computer() : Player{} {}
Computer::~Computer() {}

/**   Computer 0   **/
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


/**  Computer 1  **/
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

/**  Computer 2  **/
Computer2::Computer2() : Computer{} {} 

string Computer2::rep() {
    return "computer2";
}

Move * Computer2::decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) {
    if (cmd != "m" && cmd != "") {
        return nullptr;
    }
    return dfsMoveSearch(moves, board, round, 13);
}

double Computer2::outcome(Board * board, double score, int round, Move * move) const {
    move->Proc();
    move->Set(board);
    double res = score - (double) board->Outcome(round);
    move->Undo();
    move->RSet(board);
    return res;
}


/***  Other Functions  ***/
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