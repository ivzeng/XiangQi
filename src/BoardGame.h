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

#ifndef INIT_LANGUAGE
//  1 for Chinese; 2 for English
#define INIT_LANGUAGE 1
#endif

class Player;
class Move;
class Board;
class State;
class Msg;

//     BoardGame Class     //
// A superclass that owns the board and other game infomation. It can handle the game and produce relative messages

class BoardGame {
    protected:
    /**  Fields  **/
    std::unique_ptr<State> state;
    std::unique_ptr<Msg> msg;
    std::vector<std::string> playerType;
    std::vector<int> scores;
    std::unique_ptr<Board> board;

    int round;
    std::vector<std::unique_ptr<Move>> moves;
    std::vector<std::unique_ptr<Move>> hist;
    std::vector<std::unique_ptr<Player>> players;

    /**  Functions  **/
    
    virtual void init();

    virtual int proc(const std::string & cmd, std::string & fb);

    // starts a game
    virtual void start(std::string & fb);

    bool pSetted();

    virtual void resetPlayers();

    virtual void resetGame();

    virtual int updateMoves();

    // sets m into a string of moves' names, separated by a space
    void movesRep(std::string & m, const std::vector<std::unique_ptr<Move>> & moves) const;

    virtual void doRound(Move * move);

    virtual int undoRound();

    // analyzes the winner
    virtual int analyze() const;

    virtual int gameRound() const;
    
    virtual int pMoveIdx() const;
    
    // returns the expected number of players
    virtual int ePlayerCount() const = 0;

    virtual void updateRMsg(std::string & m) const;

    virtual void updateCmd(std::string & m) const;

    
    public:
    
    BoardGame();
    virtual ~BoardGame() = 0;

    // processes a command
    int Proc(const std::string & cmd, std::string & fb);

    // checks if the game is in the 'end' state
    bool Exited() const;

    // updates message, which requests for a command
    void UpdateRMsg(std::string & m) const;                 
};


//    XiangQi    //
class XQBoard;
class XiangQi : public BoardGame{
    
    void init() override;
    int ePlayerCount() const override;
    public:
    XiangQi();
    
};


std::unique_ptr<BoardGame> MakeBoardGame(char type);
#endif