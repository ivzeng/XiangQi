#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <memory>

class Move;
class Board;


//    Item Class   //
class Item {

    virtual double val() const = 0;    // gets the value of the Piece
    virtual double val(const std::pair<int,int> & at) const = 0;    // gets the value of the Piece at the pos 
    virtual bool valid() const = 0;  // determine if an item is valid

    public:
    Item();
    virtual ~Item() = 0;

    double Val() const;
    double Val(const std::pair<int,int> & at) const;
    bool Valid() const;

};

//    XiangQi Pieces    //
// handles move-searching; 
// is one of the following:
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
    protected:
    int type;
    int status;
    int colour;
    std::pair<int,int> pos;

    // functions
    double val() const override;
    double val(const std::pair<int,int> & at) const override;
    bool valid() const override;
    void setType(int type);
    void setCol(int col);
    public:

    XQPiece();
    void Init(int type, int colour, const std::pair<int,int> & pos);
    void Init(int type, int colour, int x, int y);

    int Type() const;
    const std::pair<int, int> & GetPos() const;
    int GetCol() const;
    void SetStatus(int stat = 1);
    void SetPos(int x, int y);
    void SetPos(const std::pair<int,int> & pos);
};
#endif