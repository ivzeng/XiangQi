#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include <queue>


/************      Player Classes      *************
 *  Classes for moves & decisions
 * 
 *  Used for:
 *      handling Moves (Human)
 *      Analyzing (long-run) outcome of each move
 *      decide an optimal move (Computer)
 * 
 **************************************************/

class BoardGame;
class Board;
class Item;
class Move;
class IO;



///****     Player Superclass     ****///

class Player {
    protected:
    /** fields **/

    /** functions **/

    virtual std::string rep() = 0; 

    // makes a move based on cmd
    virtual Move * decide(
        const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves,
        Board * board, int round
    ) = 0;

    // finds a good move with a number [depth] of simulation rounds
    virtual double outcome(
        Board * board, double score, int round, Move * move = nullptr
    ) const;

    // analyzes game's outcome
    virtual double dfsMoveAnalysis(
        Board * board, double curScore, int round, int depth
    ) const;

    // finds an optimal move with DFS
    Move * dfsMoveSearch(
        const std::vector<std::unique_ptr<Move>> & moves,
        Board * board, int round,int depth
    ) const;

    public:
    // constructor / destructor
    Player();
    virtual ~Player() = 0;

    // returns the name of the player
    std::string Rep();

    // decides or handles a move
    Move * Decide(
        const std::string & cmd, 
        std::vector<std::unique_ptr<Move>> & moves, 
        Board * board, int round
    );
};


///****    Inherited Human Player Class    ****///

class Human : public Player {
    /**   Functions   **/
    
    std::string rep() override;
    Move * decide(
        const std::string & cmd, 
        std::vector<std::unique_ptr<Move>> & moves, 
        Board * board, int round) override;

    public:
    Human();
    ~Human() override;

};

///**** Inherited Computer Player Superclass ****///

class Computer : public Player {
    
    /**   Functions   **/
    protected:
    Move * decide(const std::string & cmd, std::vector<std::unique_ptr<Move>> & moves, Board * board, int round) override;

    // returns the depth of the DFS
    virtual int depth() const = 0;

    public:
    Computer();
    virtual ~Computer() = 0;

};

///****     Computer0 Subclass     ****///

class Computer0 : public Computer {

    /**   Functions   **/
    std::string rep() override;
    int depth() const override;

    public:
    Computer0();
    ~Computer0();
};

///****     Computer1 Subclass     ****///

class Computer1 : public Computer {
    /**   Functions   **/
    std::string rep() override;
    int depth() const override;

    public:
    Computer1();
    ~Computer1() override;
};

///****     Computer2 Subclass     ****///

class Computer2: public Computer {
    /**   Functions   **/
    std::string rep() override;
    int depth() const override;
    double outcome(Board * board, double score, int round, Move * move) const override;
    public:
    Computer2();
    ~Computer2() override;
};

///****     Computer3 Subclass     ****///

class Computer3: public Computer {
    /**   Functions   **/
    std::string rep() override;
    int depth() const override;
    double outcome(Board * board, double score, int round, Move * move) const override;
    public:
    Computer3();
    ~Computer3();
};

// constructs play class based in type
std::unique_ptr<Player> makePlayer(int type);

#endif