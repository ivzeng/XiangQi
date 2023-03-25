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

Move * Player::Decide(
    const string & cmd, std::vector<std::unique_ptr<Move>> & moves,
    Board * board, int round
) {
    return decide(cmd, moves, board, round);
}

double Player::outcome(
    Board * board, double score, int round, Move * move
) const {
    return score;
}

double Player::dfsMoveAnalysis(
    Board * board, double score, int round, int depth
) const {
    vector<unique_ptr<Move>> moves{};
    board->GetMoves(round, moves);
    int l = moves.size();
    if (l == 0) {
        return -600;
    }
    depth /= l;
    priority_queue<double> scores {};
    if (depth <= l) {
        for (const unique_ptr<Move> & move : moves) {
            scores.push(outcome(board, move->Outcome()-score, round, move.get()));
        }
        return expectedOutcome(20, scores);
    }
    for (const unique_ptr<Move> & move : moves) {
        move->Proc();
        move->Set(board);
        scores.push(-dfsMoveAnalysis(board, move->Outcome()-score, round+1, depth));
        move->Undo();
        move->RSet(board);
    }
    return expectedOutcome(10, scores, 0.7);
}

Move * Player::dfsMoveSearch(
    const vector<unique_ptr<Move>> & moves, Board * board, int round
) const {
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
        double curSc = dfsMoveAnalysis(board, moves[i]->Outcome(), round+1, operations());
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

int Player::operations() const {
    return 100000;
}


/**    Human    **/
Human::Human() : Player{} {}

Human::~Human() {}

std::string Human::rep() {
    return "human";
}

Move * Human::decide(
    const string & cmd, std::vector<std::unique_ptr<Move>> & moves,
    Board * board, int round) {
    if (cmd == "hint") {
        return dfsMoveSearch(moves, board, round);
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

Move * Computer::decide(
    const string & cmd, std::vector<std::unique_ptr<Move>> & moves,
    Board * board, int round
) {
    if (cmd != "m" && cmd != "") {
        return nullptr;
    }
    return dfsMoveSearch(moves, board, round);
}

/**   Computer 0   **/
Computer0::Computer0() : Computer{} {}
Computer0::~Computer0() {}

string Computer0::rep() {
    return "computer0";
}


/**  Computer 1  **/
Computer1::Computer1() : Computer{} {}
Computer1::~Computer1() {}

string Computer1::rep() {
    return "computer1";
}

int Computer1::operations() const {
    return 2500000;
}

/**  Computer 2  **/
Computer2::Computer2() : Computer{} {}
Computer2::~Computer2() {}

string Computer2::rep() {
    return "computer2";
}

int Computer2::operations() const {
    return 200000;
}

double Computer2::outcome(
    Board * board, double score, int round, Move * move
) const {
    move->Proc();
    move->Set(board);
    double res = score - (double) board->Outcome(round+1);
    move->Undo();
    move->RSet(board);
    //cout << res << endl;
    return res;
}

/**  Computer 3  **/
Computer3::Computer3() : Computer{} {}

Computer3::~Computer3() {}

string Computer3::rep() {
    return "computer3";
}

int Computer3::operations() const {
    return 300000;
}

double Computer3::outcome(
Board * board, double score, int round, Move * move
) const {
    move->Proc();
    move->Set(board);
    double res = -board->Outcome(round, 1);
    move->Undo();
    move->RSet(board);
    //cout << res << endl;
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
    case 4:
        return make_unique<Computer3>();
    
    default:
        return nullptr;
    }
}