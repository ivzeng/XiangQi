#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <memory>
#include <utility>
#include <vector>

class Player;
class Piece;
class Move;
class Board;

//  BoardGame Class  //
// owns the board;
// analyzes / processes round and moves.

class BoardGame {
    protected:
    // fields
    int state;      // 0: in-game, 1: main page, i >= 2 : player (i-1) wins
    int round;
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Move>> moves;
    std::vector<std::unique_ptr<Move>> hist;

    virtual int init();
    virtual int update();
    virtual int take(int idx) = 0;
    virtual int undo() = 0;
    virtual bool end();
    
    public:
    BoardGame();
    virtual ~BoardGame() = 0;
    int Init();
    bool End();                    // checks if the game ends
    int Update();                  // updates game state
    int Take(int idx);             // do a move
    int Undo();                    // undo a move
};

class XiangQi : public BoardGame{
    
    int take(int idx) override;
    int undo() override;

    public:
    XiangQi();

    
};


std::unique_ptr<BoardGame> makeBoardGame(char c);
#endif