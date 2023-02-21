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
class Msg;

class Board {
    /**  Fields  **/

    /**  Functions  **/
    virtual void reset() = 0;
    virtual void set(const std::pair<int,int> & pos, Item * piece) = 0;
    virtual void getMoves(int round, std::vector<std::unique_ptr<Move>> & moves, int mode = 0) = 0;
    virtual void info(std::string & m, const Msg & msg) = 0;
    virtual int pMoveIdx(int round) const = 0;
    virtual double outcome(int round) = 0;

    public:

    // constructor / destructor
    Board();
    virtual ~Board() = 0;

    // resets / initializes
    void Reset();

    // sets pieces to pos
    void Set(const std::pair<int,int> & pos, Item * piece);

    // updates possible moves at current stage
    void GetMoves(int round, std::vector<std::unique_ptr<Move>> & moves, int mode = 0);

    // print the board information
    void Info(std::string & m, const Msg & msg);        

    // gets the index of the player to move
    int PMoveIdx(int round) const;

    // computes the outcome of a player at current stage
    double Outcome(int round);
};

// XiangQi Board //

class XQPiece;

class XQBoard : public Board {
    /**  Field  **/
    XQPiece * board[10][9];
    std::unique_ptr<XQPiece> pieces [2][16];

    /**  Functions  **/
    
    // field setting / getting
    void reset() override;
    void info(std::string & m, const Msg & msg) override;
    void setPiece(int type, int col, int x, int y, XQPiece * p);
    void set(int x, int y, XQPiece * piece);
    void set(const std::pair<int,int> & pos, Item * piece) override;
    XQPiece * get(int x, int y) const;
    XQPiece * get(const std::pair<int,int> & pos) const;

    // field information
    int width() const;
    int height() const;
    int pMoveIdx(int round) const override;
    double outcome(int round) override;
    int edgeType(int x, int y) const;

    // move analysis / scanning
    void getMoves(int round, std::vector<std::unique_ptr<Move>> & moves, int mode = 0) override;
    void scan(std::vector<std::unique_ptr<Move>> & moves, const XQPiece & piece, int mode);
    void jScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col, int mode);                   // scanning moves of Jiang
    void sScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col, int mode);                   // scanning moves of Shi
    void lScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col,  int mode,  int skip = 0);         // scanning the four line directions
    void mScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col,  int mode);                   // scanning moves of Ma
    void xScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col, int mode);                   // for Xiang
    void bScan(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int, int> & pos, int col, int mode);                   // for bing
    void insertMove(std::vector<std::unique_ptr<Move>> & moves,const std::pair<int, int> & from, const std::pair<int, int> & to, int col, int mode, bool isK = false);
    bool lInsertMove(std::vector<std::unique_ptr<Move>> & moves, const std::pair<int,int> & from, const std::pair<int,int> & to, int col, int & pass, int mode, int skip);
    bool checkLPath(int col, int & pass, XQPiece * p) const;
    bool safe(int col, const std::pair<int, int> & pos) const;


    public:
    XQBoard();

};


#endif