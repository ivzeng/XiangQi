#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include <queue>

class BoardGame;
class Board;
class Item;
class Move;
class IO;

//*****      Player Class      *****//
// handles moving
class Player {
    /** fields **/
    protected:
    
    /** functions **/

    // makes a move based on cmd
    virtual Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) = 0;

    // finds a good move with a number [depth] of simulation rounds
    virtual double outcome(Board * board, double score, int round, Move * move = nullptr) const;

    // calculates the expected outcome
    virtual double eOutcome(int l, std::priority_queue<double> & outcomes, double factor = 0.5) const;

    // analyzes moves
    virtual double dfsMoveAnalysis(Board * board, double curScore, int round, int depth) const;
    Move * dfsMoveSearch(const std::vector<std::unique_ptr<Move>> & moves, Board * board, int round,int depth) const;

    virtual std::string rep() = 0; 

    public:
    // constructor / destructor
    Player();
    virtual ~Player() = 0;

    // name of the player
    std::string Rep();
    // decides or handles a move
    Move * Decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round);
};

class Human : public Player {
    // function
    std::string rep() override;
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) override;
    public:
    Human();

};

class Computer : public Player {
    
    // derived functions
    public:
    Computer();
    virtual ~Computer() = 0;

};

class Computer0 : public Computer {

    // derived functions
    std::string rep() override;
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) override;
    public:
    Computer0();
};

class Computer1 : public Computer {
    // derived functions
    std::string rep() override;
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) override;
    public:
    Computer1();
};

class Computer2: public Computer {
    public:
    Computer2();
    std::string rep() override;
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) override;

    double outcome(Board * board, double score, int round, Move * move) const override;
};

std::unique_ptr<Player> makePlayer(int type);

#endif