#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <memory>
#include <utility>
#include <vector>
#include <string>

//      Chess Board class     //
// records the position of each peice 

class Move;

class Board {
    // sets/gets fields
    virtual void reset() = 0;
    virtual void getMoves(int round, std::vector<std::unique_ptr<Move>> & moves) = 0;
    virtual void info(std::string &) = 0;

    public:
    Board();
    virtual ~Board() = 0;
    void Reset();
    void GetMoves(int round, std::vector<std::unique_ptr<Move>> & moves);
    void Info(std::string & in);        // print the board information
};

// XiangQi Board //

class XQPiece;

class XQBoard : public Board {
    XQPiece * board[10][9];
    std::unique_ptr<XQPiece> pieces [2][16];


    // sets/gets fields
    void reset() override;
    void getMoves(int round, std::vector<std::unique_ptr<Move>> & moves) override;
    void info(std::string & in);
    void setPiece(int x, int y, XQPiece * p);
    void set(int x, int y, XQPiece * piece);
    void set(const std::pair<int,int> & pos, XQPiece * piece);
    const XQPiece & get(int x, int y) const;
    const XQPiece & get(const std::pair<int,int> & pos) const;

    // field information
    int width();
    int height();
    int pMoveIdx(int round);

    public:
    XQBoard();
};


#endif