#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <memory>
#include <utility>
#include <string>

//      Chess Board class     //
// records the position of each peice 

class Board {

    // sets/gets fields
    virtual int init() = 0;
    virtual void info(std::string &) = 0;

    public:
    Board();
    virtual ~Board() = 0;
    int Init();
    int Update(int round, std::vector<std::unique_ptr<Move>> moves);
    void Info(std::string & in);        // print the board information
};

// XiangQi Board //

class XQPiece;

class XQBoard : public Board {
    XQPiece * board[10][9];
    std::unique_ptr<XQPiece> pieces [2][16];


    // sets/gets fields
    int init() override;
    void initP(int x, int y, XQPiece * p);
    void set(int x, int y, XQPiece * piece);
    void set(const std::pair<int,int> & pos, XQPiece * piece);
    XQPiece * get(int x, int y) const;
    XQPiece * get(const std::pair<int,int> & pos) const;

    // field information
    int width();
    int height();
    void info(std::string & in);
    public:
    XQBoard();
};


#endif