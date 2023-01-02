#include "BoardGame.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

BoardGame::BoardGame() : state{1}, round {0}, board{}, moves{}, hist{}, players{}, cmds{}  {}

int BoardGame::Init() {
    return init();
}

int BoardGame::Proc(int cmd) {
    return proc(cmd);
}

bool BoardGame::Stopped() const {
    return state == 0;
}

int BoardGame::init() {
    if (board->Init() < 0) return -1;
    state = 1;
    round = 0;
    players.clear();
    moves.clear();
    hist.clear();
    updateCmds();
    return 1;
}

int BoardGame::proc(int c) {
    string & cmd = cmds[c];
    if (cmd == "start") {
        state = 2;

    }
    else if (cmd == "exit") {
        state = 0;
    }
    else if (cmd == "back") {
        state = 1;
    }
    else if (cmd == "end") {
        int winner = analyze();
        state = 1;
    }
    return state;
}

int BoardGame::update() {
    if (board->Update(round, moves) <= 0) {
        return -1;
    }
    updateCmds();
    return 1;
}

int BoardGame::take(int idx) {
    if (moves.size() <= idx) {
        return -1;
    }
    
    if (moves[idx]->Proc() == 1) {
        hist.emplace_back(move(moves[idx]));
        moves[idx] = nullptr;
        round += 1;
        return 1;
    }
    return -1;
}

int BoardGame::undo() {
    if (hist.size() == 0) return -1;
    hist[hist.size()-1]->Undo();
    hist.pop_back();
    round -= 1;
    return 1;
}

bool BoardGame::end() const {
    return moves.size();
}

void BoardGame::info(string & in, int details) const {
    in.clear();
    in.reserve(400);
    in += '\n';
    if (details > 0) {
        in += "round" + to_string(round/2+1) + ":\n";
        string b = "";
        board->Info(b);
        in += b;
        in += '\n';
    }
    if (details == 3) {
        // history
    }
    if (details >= 0) {
        in += "Player(" + to_string(round%2+1) + ") move:";
    }
    if (details >= 2) {
        // moves
    }
}

void BoardGame::updateCmds() {
    cmds.clear();
    switch (state)
    {
    case 2: // player setting
        cmds = {"h"};
        for (int i = 0; i <= 2; i += 1) {
            cmds.emplace_back("c" + to_string(i));
        }
        break;
    case 3: // setting
        cmds = {"back"};
        break;
    case 4: // game
        cmds = {"end", "undo"};
        if (dynamic_cast<Human *>(players[PMoveIdx()].get())) {
            cmds.emplace_back("show", "hint");
            for (const auto & move : moves) {
                cmds.emplace_back(move->Rep());
            }
        }
        else {
            cmds.emplace_back("m");
        }
        break;
    
    default:    // main
        cmds = {"start", "set", "score", "restart", "exit"};
        break;
    }
}


/*
void BoardGame::ValidCmds(vector<string> & cmdList) {
    validCmds(cmdList);
}

int BoardGame::Update() {
    return update();
}

int BoardGame::Take(int idx) {
    return take(idx);
}

int BoardGame::Undo() {
    return undo();
}

bool BoardGame::End() const {
    return end();
}


void BoardGame::Info(string & in, int details) const {
    in = "";
    info(in, details);
}

*/






//  XiangQi  //
XiangQi::XiangQi() : BoardGame{} {
    board = make_unique<XQBoard>();
}



