#include "Player.h"
#include "Move.h"

using namespace std;

Player::Player() {}


Move Player::decideMove(const vector<Move> & moves) {
    return decide(moves);
}

Move Human::decide(const vector<Move> & moves) {
    return moves[0];
}

Move Computer0::decide(const vector<Move> & move) {
    return move[0];
}

Move Computer1::decide(const vector<Move> & moves) {
    return moves[0];
}

unique_ptr<Player> makePlayer(int type) {
    switch (type)
    {
    case 0:
        return make_unique<Human>(type);
    case 1:
        return make_unique<Computer0>(type);
    case 2:
        return make_unique<Computer1>(type);
    
    default:
        return nullptr;
    }
}
