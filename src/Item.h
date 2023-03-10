#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <memory>

class Move;
class Board;


//    Item Class   //
class Item {
    /**   Fields   **/

    /**   Functions   **/
    virtual double val() const = 0;    
    virtual double val(const std::pair<int,int> & at) const = 0;    
    virtual bool valid() const = 0;

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

//    XiangQi Pieces    //
// handles move-searching; 
// as one of the following:
//   Jiang | Shi | Ju | Pao | Ma | Xiang | Bing

// piece types
#define XQPIECE_Jiang   1
#define XQPIECE_Shi     2
#define XQPIECE_Ju      3
#define XQPIECE_Pao     4
#define XQPIECE_Ma      5
#define XQPIECE_Xiang   6
#define XQPIECE_Bing    7



class XQPiece : public Item {
    /**   Fields   **/

    protected:
    int type;
    int status;
    int colour;
    std::pair<int,int> pos;

    /**   Functions   **/

    double val() const override;
    double val(const std::pair<int,int> & at) const override;
    bool valid() const override;
    void setType(int type);
    void setCol(int col);
    public:

    // Constructor / Destructor
    XQPiece();
    ~XQPiece();

    // initializes
    void Init(int type, int colour, const std::pair<int,int> & pos);
    void Init(int type, int colour, int x, int y);

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
};
#endif