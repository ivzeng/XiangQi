#include "BoardGame.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

BoardGame::BoardGame() : state{0}, round {0}, board{}, moves{}, hist{}  {}

int BoardGame::Init() {
    return init();
}

bool BoardGame::End() {
    return moves.size();
}

int BoardGame::init() {
    if (board->Init() < 0) return -1;
    return 1;
}


//  XiangQi  //
XiangQi::XiangQi() : BoardGame{} {
    board = make_unique<XQBoard>();
}


