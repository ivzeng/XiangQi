#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <memory>

/*************      Item Classes      **************
 *  Classes that records item/piece's info
 * 
 *  Used for:
 *      managing individual's information
 *      determining individual's value
 * 
 **************************************************/

class Move;
class Board;

///****     Item Superclass     ****///

class Item {
    /**   Fields   **/

    /**   Functions   **/  
    virtual bool valid() const                              = 0;
    virtual double val() const                              = 0;    
    virtual double val(const std::pair<int,int> & at) const = 0;  

    public:
    Item();
    virtual ~Item() = 0;

    // gets the value of the Piece
    double Val() const;

    // gets the value of the Piece at the pos 
    double Val(const std::pair<int,int> & at) const;

    // determine if an item is valid
    bool Valid() const;

};



// Chinese Chess Pieces
//      Jiang   (General) 
//      | Shi   (Advisor) 
//      | Ju    (Chariot) 
//      | Pao   (Cannon)
//      | Ma    (Horse)
//      | Xiang (Elephant) 
//      | Bing  (Pawn)

#define XQPIECE_Jiang   1
#define XQPIECE_Shi     2
#define XQPIECE_Ju      3
#define XQPIECE_Pao     4
#define XQPIECE_Ma      5
#define XQPIECE_Xiang   6
#define XQPIECE_Bing    7


///****   Chinese Chess Piece Superclass   ****///

class XQPiece : public Item {
    /**   Fields   **/

    protected:
    int type;
    int status;
    int colour;
    std::pair<int,int> pos;

    /**   Functions   **/

    void setType(int type);
    void setCol(int col);

    // returns the value of the current piece
    double val() const override;

    // returns the value of the current piece at position [at]
    double val(const std::pair<int,int> & at) const override;

    // determines if the piece is valid (i.e. it is not captured)
    bool valid() const override;

    public:
    XQPiece();
    ~XQPiece();

    // returns piece type
    int Type() const;

    // returns piece position
    const std::pair<int, int> & GetPos() const;

    // returns piece colour
    int GetCol() const;

    // sets piece status, default 1 (valid)
    void SetStatus(int stat = 1);

    // sets piece positions
    void SetPos(int x, int y);
    void SetPos(const std::pair<int,int> & pos);

    // initializes the piece
    void Init(int type, int colour, const std::pair<int,int> & pos);
    void Init(int type, int colour, int x, int y);
};

#endif