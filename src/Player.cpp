#include "Player.h"
#include "BoardGame.h"
#include "Move.h"
#include "Board.h"

using namespace std;

Player::Player() {}

Player::~Player() {}

string Player::Rep() {
    return rep();
}

Move * Player::Decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round) {
    return decide(cmd, moves, board, round);
}

Move * Player::smartMove(vector<unique_ptr<Move>> & moves, Board & board, int round, int depth) {
    return moves[0].get();
}

//    Human    //
Human::Human() : Player{} {}

std::string Human::rep() {
    return "human";
}

Move * Human::decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round) {
    if (cmd == "hint") {
        return smartMove(moves, board, round, 3);
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

Move * Computer0::decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round) {
    return moves[0].get();
}

//  Computer 1  //
Computer1::Computer1() : Computer{} {}
string Computer1::rep() {
    return "computer1";
}

Move * Computer1::decide(const string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round) {
    return moves[0].get();
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