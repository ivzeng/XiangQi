#include "Player.h"
#include "BoardGame.h"
#include "Move.h"
#include "Board.h"
#include "helpers.h"
#include <iostream>
#include <algorithm>

using namespace std;


/**   Player   **/

Player::Player() {}

Player::~Player() {}

string Player::Rep() {
    return rep();
}

Move * Player::Decide(
    Board * board, int round,
    const string & cmd,
    vector<unique_ptr<Move>> & moves
) {
    return decide(board, round, cmd, moves);
}

void Player::initMovesEPayoff(
    const vector<unique_ptr<Move>> & moves,
    vector<pair<double, Move *>> & movesEPayoff
) const {
    int ml = moves.size();
    movesEPayoff = vector<pair<double, Move *>>(ml, pair<double, Move *>{0, nullptr});
    for (int i = 0; i < ml; i += 1){
        movesEPayoff[i].second = moves[i].get();
    }
}

double Player::eOutcome(
    Board * board, int round
) const {
        return board->Outcome(round, 0);
}

double Player::eOutcome(
    int l, double factor,
    const vector<pair<double, Move *>> & movesEPayoff
) const {
    
    // calculate expected outcome
    double res = 0;
    double remain = 1;
    if ((int)movesEPayoff.size() <= l) {
        l = movesEPayoff.size()-1;
    }
    for (int i = 0; i < l; i += 1) {
        res += (double) movesEPayoff[i].first*remain*factor;
        remain *= (1-factor);
    }
    res += (double) movesEPayoff[l].first*remain;
    return res;
}

double Player::dfsMovesAnalysis(
    Board * board, int round, int depth,
    vector<pair<double, Move *>> & movesEPayoff
) const {
    int n = movesEPayoff.size();

    // case: there is no avaliable move, the opponent wins
    if (n == 0) {
        return -600;
    }

    // analyze the expected payoff of each move and store it into movesEPayoff
    round += 1;
    depth /= n;
    for (pair<double, Move *> & move : movesEPayoff) {
        move.second->Proc();
        move.second->Set(board);

        if (depth <= 1) {
            move.first = eOutcome(board, round);
        }
        else {
            vector<unique_ptr<Move>> nextMoves{};
            vector<pair<double, Move *>> nextMovesEPayoff{};
            board->GetMoves(round, nextMoves);
            initMovesEPayoff(nextMoves, nextMovesEPayoff);
            move.first = dfsMovesAnalysis(board, round, depth, nextMovesEPayoff);
        }

        move.second->Undo();
        move.second->RSet(board);
    }

    // sort movesEPayoff by payoff into accending order
    sort(
        movesEPayoff.begin(), movesEPayoff.end(),
        [] (const pair<double, Move *> & m1, const pair<double, Move *> & m2) -> bool {
            return m1.first < m2.first;
        }
    );

    /*
    #ifdef DEBUG
    cout << "Round " << round - 1 << endl; 
    for (const auto & m : movesEPayoff) {
        cout << m.second->Rep() << " " << m.first << endl; 
    }
    cout << endl;
    #endif
    */

    // calculates the overall outcome
    int l = (n <= 1) ? 20 : 10;
    double factor = (n <= 1) ? (double)0.5 : (double)0.7;
    return -eOutcome(l, factor, movesEPayoff);
}

void Player::analyzeMoves(
    Board * board, int round, vector<pair<double, Move *>> & movesEPayoff
) const {
    dfsMovesAnalysis(board, round, operations(), movesEPayoff);
}

Move * Player::selectMove(
    const std::vector<std::pair<double, Move *>> & movesEPayoff
) const {
    return movesEPayoff[0].second;
}

Move * Player::decideMove(
    Board * board, int round, const vector<unique_ptr<Move>> & moves
) const {
    if (moves.size() == 0) {
        return nullptr;
    }
    else if (moves.size() == 1) {
        return moves[0].get();
    }
    vector<pair<double, Move *>> movesEPayoff{};
    initMovesEPayoff(moves, movesEPayoff);
    analyzeMoves(board, round, movesEPayoff);
    #ifdef DEBUG
    cout << "Round " << round << endl; 
    for (const auto & m : movesEPayoff) {
        cout << m.second->Rep() << " " << m.first << endl; 
    }
    cout << endl;
    #endif
    return selectMove(movesEPayoff);
}

int Player::operations() const {
    return 50000;
}


/**    Human    **/
Human::Human() : Player{} {}

Human::~Human() {}

std::string Human::rep() {
    return "human";
}

Move * Human::decide(
    Board * board, int round,
    const string & cmd,
    vector<unique_ptr<Move>> & moves
) {
    if (cmd == "hint") {
        return decideMove(board, round, moves);
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
    Board * board, int round,
    const string & cmd,
    vector<unique_ptr<Move>> & moves
) {
    if (cmd != "m" && cmd != "") {
        return nullptr;
    }
    return decideMove(board, round, moves);
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
    return 6500000;
}

/**  Computer 2  **/
Computer2::Computer2() : Computer{} {}
Computer2::~Computer2() {}

string Computer2::rep() {
    return "computer2";
}

int Computer2::operations() const {
    return 4000000;
}

double Computer2::eOutcome(Board * board, int round) const {
    return board->Outcome(round, 1);
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

double Computer3::eOutcome(
Board * board, int round
) const {
    return board->Outcome(round, 2);
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