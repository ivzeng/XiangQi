#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <memory>
#include <utility>
#include <vector>
#include <string>

class Player;
class Move;
class Board;

//  BoardGame Class  //
// owns the board;
// analyzes / processes round and moves.

class BoardGame {
    protected:
    // fields
    int state;      // 0: ended, 1: main page, 2: setting player, 3: setting, 4: game
    int round;
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Move>> moves;
    std::vector<std::unique_ptr<Move>> hist;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::string> cmds;

    virtual int init();
    virtual int proc(int cmd);
    virtual int update();
    virtual int take(int idx);
    virtual int undo();
    virtual bool end() const;
    virtual void info(std::string & in, int details) const;
    virtual void updateCmds();

    int analyze();  // analyzes the winner
    
    public:
    BoardGame();
    virtual ~BoardGame() = 0;
    int Init();
    int Proc(int cmd);
    bool Stopped() const;
    
    int PMoveIdx() const;
    int GetState() const;
    const std::vector<std::string> & GetCmds() const;
    /*
    int Update();                  // updates game state
    int Take(int idx);             // do a move
    int Undo();                    // undo a move
    bool End() const;              // checks if the game ends
    
    void Info(std::string & in, int details) const;      // stores the game information
    */
};


// XiangQi //
class XiangQi : public BoardGame{
    int round;
    std::unique_ptr<XQBoard> board;
    std::vector<std::unique_ptr<Move>> moves;
    std::vector<std::unique_ptr<Move>> hist;

    int init() override;
    public:
    XiangQi();
    
};


std::unique_ptr<BoardGame> makeBoardGame(char c);
#endif