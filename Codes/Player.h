#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

class Board;
class Piece;
class Move;

//      Player Class      //
// makes/decides each move
class Player {
    // fields //
    protected:
    
    // functions //
    virtual Move decide(const std::vector<Move> & moves) = 0;

    public:
    // constructor / destructor
    Player();
    virtual ~Player() = 0;

    // processing
    Move decideMove(const std::vector<Move> & moves);
};

class Human : public Player {

    // function
    public:
    Move decide(const std::vector<Move> & moves) override;

};

class Computer0 : public Player {
    
    // derived functions
    public:
    Move decide(const std::vector<Move> & moves) override;
};

class Computer1 : public Player {

    // derived functions
    public:
    Move decide(const std::vector<Move> & moves) override;
};

std::unique_ptr<Player> makePlayer(int type);

#endif