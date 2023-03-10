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
    /**   Functions   **/
    std::string rep() override;
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) override;
    public:
    Human();
    ~Human() override;

};

class Computer : public Player {
    
    /**   Functions   **/
    protected:
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) override;
    virtual int depth() const = 0;

    public:
    Computer();
    virtual ~Computer() = 0;
    
    

};

class Computer0 : public Computer {

    /**   Functions   **/
    std::string rep() override;
    int depth() const override;

    public:
    Computer0();
    ~Computer0();
};

class Computer1 : public Computer {
    /**   Functions   **/
    std::string rep() override;
    int depth() const override;

    public:
    Computer1();
    ~Computer1() override;
};

class Computer2: public Computer {
    /**   Functions   **/
    std::string rep() override;
    int depth() const override;
    double outcome(Board * board, double score, int round, Move * move) const override;
    public:
    Computer2();
    ~Computer2() override;
};

class Computer3: public Computer {
    /**   Functions   **/
    std::string rep() override;
    int depth() const override;
    double outcome(Board * board, double score, int round, Move * move) const override;
    public:
    Computer3();
    ~Computer3();
};

std::unique_ptr<Player> makePlayer(int type);

#endif