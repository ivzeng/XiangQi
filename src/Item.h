#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <memory>

class Move;
class Board;


//    Item Class   //
class Item {

    virtual int val() const = 0;    // gets the value of the Piece
    virtual char rep() const = 0;   // gets the charactor representation
    virtual bool valid() const = 0;  // determine if an item is valid

    public:
    Item();
    virtual ~Item() = 0;

    int Val() const;
    char Rep() const;
    bool Valid() const;

};

//    XiangQi Pieces    //
// handles move-searching; 
// is one of the following:
//   Jiang | Shi | Ju | Pao | Ma | Xiang | Bing
class XQPiece : public Item {
    protected:
    int type;
    int status;
    int colour;
    std::pair<int,int> pos;

    // functions
    char rep() const override;
    int val() const override;
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