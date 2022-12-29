#ifndef BOARD_H
#define BOARD_H

#include <utility>


class Piece;


//      Board class     //
// a 10 * 9 XiangQi board
class Board {
    Piece * board[10][9];
    
    public:
    Board();

    // sets/gets fields
    void set(int x, int y, Piece * piece);
    void set(const std::pair<int,int> & pos, Piece * piece);
    Piece * get(int x, int y);
    Piece * get(const std::pair<int,int> & pos);

};

#endif