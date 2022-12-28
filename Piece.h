#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>

class Move;
class Board;

//      Piece Class     //
// handles move-searching; 
// is one of the following:
//   Jiang | Shi | Ju | Pao | Xiang | Ma | Bing
class Piece {
    protected:
    int status;
    std::pair<int,int> pos;

    // virtual functions
    virtual int val() = 0;

    public:

    Piece(const std::pair<int,int> & pos);
    virtual ~Piece() = 0;

    void setStatus();
    int value();
    

    
};

#endif