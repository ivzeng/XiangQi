#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <map>


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

#define PLAYER_HU    0
#define PLAYER_C0   1
#define PLAYER_C1   2
#define PLAYER_C2   3
#define PLAYER_C3   4
#define PLAYER_C4   5


///****     Player Superclass     ****///

class Player {
    protected:
    /** fields **/

    /** functions **/

    virtual std::string rep() const = 0;

    virtual int type() const = 0;

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
    );

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
    );

    // analyze moves
    virtual double analyzeMoves(
        Board * board, int round,
        std::vector<std::pair<double, Move *>> & movesEPayoff
    );

    // store informations
    virtual void storeInfo(
        Board * board, int round, double expectedPayoff,
        const std::vector<std::pair<double, Move *>> & movesEPayoff
    );

    // select a move
    virtual Move * selectMove(
        const std::vector<std::pair<double, Move *>> & movesEPayoff
    ) const;

    // decide a move
    Move * decideMove(
        Board * board, int round,
        const std::vector<std::unique_ptr<Move>> & moves
    );


    // returns the depth of the DFS
    virtual int operations() const;


    public:
    // constructor / destructor
    Player();
    virtual ~Player() = 0;

    // returns the name of the player
    std::string Rep() const;

    int Type() const;

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
    
    std::string rep() const override;
    int type() const override;
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

    // randomly select a move based on prob on a sorted list of moves
    Move * rSelectMove(
        const std::vector<std::pair<double, Move *>> & movesEPayoff,
        float prob = 0.7, float range = 0.5
    ) const;

    public:
    Computer();
    virtual ~Computer() = 0;

};

///****     Computer0 Subclass     ****///

class Computer0 : public Computer {

    /**   Functions   **/
    std::string rep() const override;
    int type() const override;

    public:
    Computer0();
    ~Computer0();
};

///****     Computer1 Subclass     ****///

class Computer1 : public Computer {
    /**   Functions   **/
    std::string rep() const override;
    int type() const override;
    int operations() const override;

    public:
    Computer1();
    ~Computer1() override;
};

///****     Computer2 Subclass     ****///

class Computer2: public Computer {
    /**   Functions   **/
    std::string rep() const override;
    int type() const override;
    int operations() const override;
    double eOutcome(Board * board, int round) override;
    public:
    Computer2();
    ~Computer2() override;
};

///****     Computer3 Subclass     ****///

class Computer3: public Computer {
    /**   Functions   **/
    std::string rep() const override;
    int type() const override;
    int operations() const override;
    double eOutcome(Board * board, int round) override;
    Move * selectMove(
        const std::vector<std::pair<double, Move *>> & movesEPayoff
    ) const override;
    public:
    Computer3();
    ~Computer3();
};


///****     Computer4 Subclass     ****///

class Computer4: public Computer {
    /**    Fields    **/

    // time points and expected outcomes
    static int dCount;
    static std::map<std::string, double> etpo;
    // time points and board outcomes
    //static std::queue<std::string> timePoints;
    //static std::unordered_map<std::string, double> btpo;

    /**   Functions   **/
    std::string rep() const override;
    int type() const override;
    int operations() const override;
    double eOutcome(Board * board, int round) override;
    void storeInfo(
        Board * board, int round, double expectedPayoff,
        const std::vector<std::pair<double, Move *>> & movesEPayoff
    ) override;
    Move * selectMove(
        const std::vector<std::pair<double, Move *>> & movesEPayoff
    ) const override;

    // file management
    void init();
    std::string fileDir();
    std::string dataDir();
    std::string fileName();
    void initTpoFile();
    void updateTpo();
    void updateTpoFile();

    public:
    Computer4();
    ~Computer4();
};

// constructs play class based in type
std::unique_ptr<Player> makePlayer(int type);

#endif