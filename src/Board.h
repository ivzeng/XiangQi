#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <memory>
#include <utility>
#include <vector>
#include <string>


/************      Board Classes      **************
 *  Classes that record the position of each peice
 * 
 *  Used for:
 *      visualing the game board
 *      analyzing the game status
 *      updating items on each move
 * 
 **************************************************/

class Move;
class Item;
class Msg;
class XQPiece;


///****     Board Superclass     ****///
class Board {
    /**  Fields  **/

    /**  Functions  **/
    virtual void reset()                                            = 0;
    virtual void set(const std::pair<int,int> & pos, Item * piece)  = 0;
    virtual void getMoves(
        int round, std::vector<std::unique_ptr<Move>> & moves, 
        int mode = 0
    )                                                               = 0;
    virtual void info(std::string & m, const Msg & msg)             = 0;
    virtual int pMoveIdx(int round) const                           = 0;
    virtual double outcome0(int round)                              = 0;
    virtual double outcome1(int round)                              = 0;


    public:

    // constructor, destructor
    Board();
    virtual ~Board() = 0;

    // resets / initializes
    void Reset();

    // sets pieces to pos
    void Set(const std::pair<int,int> & pos, Item * piece);

    // updates possible moves at current stage
    void GetMoves(
        int round, std::vector<std::unique_ptr<Move>> & moves,
        int mode = 0
    );

    // print the board information
    void Info(std::string & m, const Msg & msg);        

    // gets the index of the player to move
    int PMoveIdx(int round) const;

    // computes the outcome of a player at current stage
    double Outcome(int round, int mode = 0);
};


///****     Chinese Chess Board Subclass     ****///
class XQBoard : public Board {
    /**  Field  **/
    XQPiece * board[10][9];
    std::unique_ptr<XQPiece> pieces [2][16];

    /**  Functions  **/
    
    // field setting / getting //
    void reset() override;

    void info(std::string & m, const Msg & msg) override;

    void setPiece(int type, int col, int x, int y, XQPiece * p);

    void set(int x, int y, XQPiece * piece);

    void set(const std::pair<int,int> & pos, Item * piece) override;

    XQPiece * get(int x, int y) const;

    XQPiece * get(const std::pair<int,int> & pos) const;

    // field information //
    int width() const;

    int height() const;

    int pMoveIdx(int round) const override;

    double outcome0(int round) override;

    double outcome1(int round) override;



    int edgeType(int x, int y) const;

    // overall move-scan
    void getMoves(
        int round, std::vector<std::unique_ptr<Move>> & moves, 
        int mode = 0
    ) override;

    // individual move-scan
    void scan(
        std::vector<std::unique_ptr<Move>> & moves, 
        const XQPiece & piece,
        int mode
    );

    // move-scan for Jiang (General)
    void jScan(
        std::vector<std::unique_ptr<Move>> & moves,
        const std::pair<int, int> & pos, int col, int mode
    );

    // move-scan for the Shi (Advisor)
    void sScan(
        std::vector<std::unique_ptr<Move>> & moves,
        const std::pair<int, int> & pos, int col, int mode
    );

    // move-scan for the Ju (Chariot) or the Pao (Cannon)
    void lScan(
        std::vector<std::unique_ptr<Move>> & moves,
        const std::pair<int, int> & pos, int col,  
        int mode,  int skip = 0
    );

    // move-scan for the Ma (horse)
    void mScan(
        std::vector<std::unique_ptr<Move>> & moves,
        const std::pair<int, int> & pos, int col,  int mode
    );

    // move-scan for the Xiang (Elephant)
    void xScan(
        std::vector<std::unique_ptr<Move>> & moves, 
        const std::pair<int, int> & pos, int col, int mode);

    // move-scan for the Bing (Pawn)
    void bScan(
        std::vector<std::unique_ptr<Move>> & moves,
        const std::pair<int, int> & pos, int col,
        int mode
    );

    // inserts a move if it is valid
    void insertMove(
        std::vector<std::unique_ptr<Move>> & moves,
        const std::pair<int, int> & from, const std::pair<int, int> & to, 
        int col, int mode, bool isK = false
    );

    // inserts a move if it is valid (specifically for Ju and the Pao)
    bool lInsertMove(
        std::vector<std::unique_ptr<Move>> & moves,
        const std::pair<int,int> & from, const std::pair<int,int> & to,
        int col, int & pass, int mode, int skip
    );

    // determines if a pos is safe
    bool safe(int col, const std::pair<int, int> & pos) const;

    // determines if piece p can attack 
    bool checkLPath(int col, int & pass, XQPiece * p) const;

    public:
    XQBoard();

};


#endif