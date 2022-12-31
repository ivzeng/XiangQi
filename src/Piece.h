#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>

class Move;
class Board;


//    Item Class   //
class Item {

    virtual int val() const = 0;    // gets the value of the Piece
    virtual char rep() const = 0;   // gets the charactor representation

    public:
    Item();
    virtual ~Item() = 0;

    int Val() const;
    char Rep() const;

};

//    XiangQi Pieces    //
// handles move-searching; 
// is one of the following:
//   Jiang | Shi | Ju | Pao | Ma | Xiang | Bing
class XQPiece : public Item {
    protected:
    int status;
    int colour;
    std::pair<int,int> pos;

    // functions
    void setStatus(int stat = 1);
    void setPos(int x, int y);
    void setPos(const std::pair<int,int> & pos);
    
    public:

    XQPiece(int colour);
    virtual ~XQPiece() = 0;
    void Init(const std::pair<int,int> & pos);
    void Init(int x, int y);
};

class Jiang : public XQPiece {
    public:
    Jiang(int colour);
    int val() const override;
    char rep() const override;
};

class Shi : public XQPiece {
    public:
    Shi(int colour);
    int val() const override;
    char rep() const override;

};

class Ju : public XQPiece {
    public:
    Ju(int colour);
    int val() const override;
    char rep() const override;

};

class Pao : public XQPiece {
    public:
    Pao(int colour);
    int val() const override;
    char rep() const override;

};

class Xiang : public XQPiece {
    public:
    Xiang(int colour);
    int val() const override;
    char rep() const override;

};

class Ma : public XQPiece {
    public:
    Ma(int colour);
    int val() const override;
    char rep() const override;

};

class Bing : public XQPiece {
    public:
    Bing(int colour);
    int val() const override;
    char rep() const override;
};

#endif