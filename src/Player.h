#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

class Board;
class Item;
class Move;
class IO;

//      Player Class      //
// makes/decides each move
class Player {
    // fields //
    protected:
    
    // functions //
    virtual int decide(const std::vector<Move> & moves, Board * board) = 0;

    public:
    // constructor / destructor
    Player();
    virtual ~Player() = 0;

    // processing
    int Decide(const std::vector<Move> & moves, Board * board);
};

class Human : public Player {
    std::unique_ptr<IO> io;
    // function
    public:
    int decide(const std::vector<Move> & moves, Board * board) override;

};

class Computer0 : public Player {
    
    // derived functions
    public:
    int decide(const std::vector<Move> & moves, Board * board) override;
};

class Computer1 : public Player {

    // derived functions
    public:
    int decide(const std::vector<Move> & moves, Board * board) override;
};

std::unique_ptr<Player> makePlayer(int type);

#endif