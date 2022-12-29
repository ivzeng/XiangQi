#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Game::Game() : round {0} {}

int Game::init(int * playerTypes) {
    board = nullptr;
    board = make_unique<Board>();
    
    for (int i = 0; i <= 1; i += 1) {
        for (int j = 0; j < 16; j += 1) {
            pieces[i][j] = nullptr;
        }
        // initializes pieces and puts them into the board
        pair<int,int> pPos{4, 9*i};
        pieces[i][0] = make_unique<Jiang> (i, pPos);
        board->set(pPos, pieces[i][0].get());

        pPos.first = 3;
        pieces[i][1] = make_unique<Shi> (i, pPos);
        board->set(pPos, pieces[i][1].get());

        pPos.first = 5;
        pieces[i][2] = make_unique<Shi> (i, pPos);
        board->set(pPos, pieces[i][2].get());

        pPos.first = 0;
        pieces[i][3] = make_unique<Ju> (i, pPos);
        board->set(pPos, pieces[i][3].get());

        pPos.first = 8;
        pieces[i][4] = make_unique<Ju> (i, pPos);
        board->set(pPos, pieces[i][4].get());

        pPos.first = 1;
        pieces[i][7] = make_unique<Ma> (i, pPos);
        board->set(pPos, pieces[i][7].get());

        pPos.first = 7;
        pieces[i][8] = make_unique<Ma> (i, pPos);
        board->set(pPos, pieces[i][8].get());

        pPos.first = 2;
        pieces[i][9] = make_unique<Xiang> (i, pPos);
        board->set(pPos, pieces[i][9].get());

        pPos.first = 6;
        pieces[i][10] = make_unique<Xiang> (i, pPos);
        board->set(pPos, pieces[i][10].get());

        pPos.second = 2 + 5*i;
        pPos.first = 1;
        pieces[i][5] = make_unique<Pao> (i, pPos);
        board->set(pPos, pieces[i][5].get());

        pPos.first = 7;
        pieces[i][6] = make_unique<Pao> (i, pPos);
        board->set(pPos, pieces[i][6].get());

        pPos.second = 3 + 3*i;
        pPos.first = 0;
        for (int pc = 0; pc <= 4; pc += 1) {
            pieces[i][11+pc] = make_unique<Bing> (i, pPos);
            board->set(pPos, pieces[i][11+pc].get());
            pPos.first += 2;
        }

        // initializes and set player
        players[i] = nullptr;
        players[i] = makePlayer(playerTypes[i]);
    }
    return 1;
}