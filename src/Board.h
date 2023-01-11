#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <memory>
#include <utility>
#include <vector>
#include <string>

//      Chess Board class     //
// records the position of each peice 

class Move;
class Item;

class Board {
    // sets/gets fields
    virtual void reset() = 0;
    virtual void set(const std::pair<int,int> & pos, Item * piece) = 0;
    virtual void getMoves(int round, std::vector<std::unique_ptr<Move>> & moves) = 0;
    virtual void info(std::string &) = 0;

    public:
    Board();
    virtual ~Board() = 0;
    void Reset();
    void Set(const std::pair<int,int> & pos, Item * piece);
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
    void info(std::string & in);
    void setPiece(int type, int col, int x, int y, XQPiece * p);
    void set(int x, int y, XQPiece * piece);
    void set(const std::pair<int,int> & pos, Item * piece) override;
    XQPiece * get(int x, int y);
    XQPiece * get(const std::pair<int,int> & pos);

    // field information
    int width();
    int height();
    int pMoveIdx(int round);

    // move analysis
    void getMoves(int round, std::vector<std::unique_ptr<Move>> & moves) override;
    void scan(std::vector<std::unique_ptr<Move>> & moves, const XQPiece & piece);
    void jScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col);                   // scanning moves of Jiang
    void sScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col);                   // scanning moves of Shi
    void lScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col,  int skip = 0);         // scanning the four line directions
    void mScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col);                   // scanning moves of Ma
    void xScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col);                   // for Xiang
    void bScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col);                   // for bing
    void insertMove(std::vector<std::unique_ptr<Move>> & moves,const std::pair<int, int> & from, const std::pair<int, int> & to, int col, bool isK = false);
    bool lInsertMove(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int,int> & from, const std::pair<int,int> & to, int col, int & pass, int skip);
    bool safe(int col, const std::pair<int, int> & pos) const;


    public:
    XQBoard();

};


#endif