#ifndef GAME_H
#define GAME_H

#include <memory>
#include <utility>
#include <vector>


class Player;
class Piece;
class Move;
class Board;

//  Game Class  //
// owns the board and players;
// analyzes round and moves.

class Game{
    int round;
    std::unique_ptr<Board> board;
    std::unique_ptr<Player> players [2];
    std::vector<Move> moves;
    std::vector<Move> hist;

    public:
    Game();
    void init(char * playerTypes);

};

#endif