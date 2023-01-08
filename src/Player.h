#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

class BoardGame;
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
    // makes a move based on cmd
    virtual Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round) = 0;

    // finds a good move with a number [depth] of simulation rounds
    virtual Move * smartMove(std::vector<std::unique_ptr<Move>> & moves, Board & board, int round, int depth);
    virtual std::string rep() = 0; 

    public:
    // constructor / destructor
    Player();
    virtual ~Player() = 0;

    // id
    std::string Rep();
    // processing
    Move * Decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round);
};

class Human : public Player {
    // function
    public:
    Human();
    std::string rep() override;
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round) override;

};

class Computer : public Player {
    
    // derived functions
    public:
    Computer();
    virtual ~Computer() = 0;

};

class Computer0 : public Computer {

    // derived functions
    public:
    Computer0();
    std::string rep() override;
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round) override;
};

class Computer1 : public Computer {

    // derived functions
    public:
    Computer1();
    std::string rep() override;
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board & board, int round) override;
};

std::unique_ptr<Player> makePlayer(int type);

#endif