#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

class Board;
class Piece;
class Move;

//      Player Class      //
// makes/decides each move
class Player {
    protected:
    std::unique_ptr<Piece> pieces [17];

    virtual Move decide();
    public:
    Player();
    void init();
    void searchMoves(Board * board, std::vector<Move> & moves);
    Move decideMove();
};

#endif