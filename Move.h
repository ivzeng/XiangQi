#ifndef Move_H
#define Move_H
#include <utility>

class Game;
class Piece;

class Move {
    std::pair<int, int> from;
    std::pair<int, int> to;
    Piece * target;
    Piece * captured;
    Move (const std::pair<int, int> & from, const std::pair<int, int> & to, Piece * target, Piece * captured = nullptr);

    public:
    void process(Game * game);
    int value();
};


#endif