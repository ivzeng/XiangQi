#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <memory>
#include <utility>
#include <vector>
#include <string>

// command lists
#define CMD_End     0
#define CMD_ToMain  1
#define CMD_ToS     2
#define CMD_ToPS    3
#define CMD_ResetP  7
#define CMD_ResetS  8
#define CMD_SetL    9
#define CMD_ShowC   15
#define CMD_ShowB   16
#define CMD_ShowH   17
#define CMD_ShowM   18
#define CMD_Undo    21
#define CMD_Hint    22



class Player;
class Move;
class Board;
class State;
class Msg;

//  BoardGame Class  //
// owns the board;
// analyzes / processes round and moves.

class BoardGame {
    protected:
    // fields
    std::unique_ptr<State> state;
    int round;
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Move>> moves;
    std::vector<std::unique_ptr<Move>> hist;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<int> scores;
    std::vector<std::string> playerType;
    std::unique_ptr<Msg> msg;

    virtual void init();        // init player type
    virtual void resetPlayers();      // resets players 
    virtual void resetGame();      // resets board and history; updates moves 
    virtual int proc(const std::string & cmd, std::string & fb);
    virtual void start(std::string & fb);
    bool pSetted();
    virtual int updateMoves();
    void movesRep(std::string & m, const std::vector<std::unique_ptr<Move>> & moves) const;
    virtual void doRound(Move * move);
    virtual int undoRound();
    virtual int analyze() const;  // analyzes the winner

    virtual int gameRound() const;
    virtual int pMoveIdx() const;
    virtual int ePlayerCount() const = 0;       // returns the expected number of players

    virtual void updateRMsg(std::string & m) const;
    virtual void updateCmd(std::string & m) const;

    
    public:
    BoardGame();
    virtual ~BoardGame() = 0;
    // processes a command
    // return type: -1: invalid command, 0: ... 
    int Proc(const std::string & cmd, std::string & fb);    // processes a cmd and puts the feedback message into fb. 
    bool Exited() const;

    void UpdateRMsg(std::string & m) const;                 // updates message requesting a command
};


// XiangQi //
class XQBoard;
class XiangQi : public BoardGame{
    
    void init() override;
    int ePlayerCount() const override;
    public:
    XiangQi();
    
};


std::unique_ptr<BoardGame> MakeBoardGame(char type);
#endif