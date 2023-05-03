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
        Board * board, int round,
        const std::string & cmd,
        std::vector<std::unique_ptr<Move>> & moves
    ) = 0;

    // initialize the vector that records the expected payoff of each move
    void initMovesEPayoff(
        const std::vector<std::unique_ptr<Move>> & moves,
        std::vector<std::pair<double, Move *>> & moveEPayoff
    ) const;

    // returns the immediate outcome of the board at the selected round
    virtual double eOutcome(
        Board * board, int round
    ) const;

    // returns the overall outcome
    double eOutcome(
        int l, double factor,
        const std::vector<std::pair<double, Move *>> & movesEPayoff
    ) const;

    // analyzes the payoffs of each possible moves at movesEPayoff;
    //  returns the expected (overall) outcome
    double dfsMovesAnalysis(
        Board * board, int round, int depth,
        std::vector<std::pair<double, Move *>> & movesEPayoff
    ) const;

    // analyze moves
    virtual void analyzeMoves(
        Board * board, int round,
        std::vector<std::pair<double, Move *>> & movesEPayoff
    ) const;

    // select a move (only called when there are more than one option)
    virtual Move * selectMove(
        const std::vector<std::pair<double, Move *>> & movesEPayoff
    ) const;

    // decide a move (default)
    Move * decideMove(
        Board * board, int round,
        const std::vector<std::unique_ptr<Move>> & moves
    ) const;


    // returns the depth of the DFS
    virtual int operations() const;


    public:
    // constructor / destructor
    Player();
    virtual ~Player() = 0;

    // returns the name of the player
    std::string Rep();

    // decides or handles a move
    Move * Decide(
        Board * board, int round,
        const std::string & cmd, 
        std::vector<std::unique_ptr<Move>> & moves
    );
};


///****    Inherited Human Player Class    ****///

class Human : public Player {
    /**   Functions   **/
    
    std::string rep() override;
    Move * decide(
        Board * board, int round,
        const std::string & cmd, 
        std::vector<std::unique_ptr<Move>> & moves
    ) override;

    public:
    Human();
    ~Human() override;

};

///**** Inherited Computer Player Superclass ****///

class Computer : public Player {
    
    /**   Functions   **/
    protected:
    Move * decide(
        Board * board, int round,
        const std::string & cmd,
        std::vector<std::unique_ptr<Move>> & moves
    ) override;

    public:
    Computer();
    virtual ~Computer() = 0;

};

///****     Computer0 Subclass     ****///

class Computer0 : public Computer {

    /**   Functions   **/
    std::string rep() override;

    public:
    Computer0();
    ~Computer0();
};

///****     Computer1 Subclass     ****///

class Computer1 : public Computer {
    /**   Functions   **/
    std::string rep() override;
    int operations() const override;

    public:
    Computer1();
    ~Computer1() override;
};

///****     Computer2 Subclass     ****///

class Computer2: public Computer {
    /**   Functions   **/
    std::string rep() override;
    int operations() const override;
    double eOutcome(Board * board, int round) const override;
    public:
    Computer2();
    ~Computer2() override;
};

///****     Computer3 Subclass     ****///

class Computer3: public Computer {
    /**   Functions   **/
    std::string rep() override;
    int operations() const override;
    double eOutcome(Board * board, int round) const override;
    public:
    Computer3();
    ~Computer3();
};

// constructs play class based in type
std::unique_ptr<Player> makePlayer(int type);

#endif