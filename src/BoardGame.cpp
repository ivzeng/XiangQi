#include "BoardGame.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Item.h"
#include "State.h"
#include <iostream>

using namespace std;

BoardGame::BoardGame() : state{nullptr}, round {0}, board{}, moves{}, hist{}, players{}, scores{}, playerType{}  {
    init();
}

BoardGame::~BoardGame() {}

int BoardGame::Proc(const std::string & cmd, std::string & fb) {
    return proc(cmd, fb);
}

bool BoardGame::Exited() const {
    return state->GetState() == 0;
}

void BoardGame::UpdateRMsg(string & m) const {
    updateRMsg(m);
} 


void BoardGame::init() {
    state = make_unique<State_Default>();
    playerType.emplace_back("h");
    playerType.emplace_back("c0");
    playerType.emplace_back("c1");
}

void BoardGame::resetPlayers() {
    players.clear();
}

void BoardGame::resetGame() {
    round = 0;
    board->Reset();
    hist.clear();
    updateMoves();
}


int BoardGame::proc(const string & cmd, string & fb) {
    fb.clear();
    switch(state->ReadCmd(cmd)) {
    case CMD_End: // game ended
        state->SetState(STATE_End);
        return 0;
    case CMD_ToMain: // to main manu
        state->SetState(STATE_Main);
        return 1;
    case CMD_ToS:    // to setting
        state->SetState(STATE_Setting);
        return 1;
    case CMD_ToPS:  // to player setting
        if (pSetted()) {
            fb.reserve(100);
            start(fb);
        }
        else {
            state->SetState(STATE_PSetting);
        }
        return 1;
    case CMD_ResetP:    // resetting players
        players.clear();
        fb = "Resetted players.\n";
        return 1;
    case CMD_ShowC:
        fb.reserve(200);
        updateCmd(fb);
        fb += '\n';
        return 1;
    case CMD_ShowB:     // showing board
        fb.reserve(300);
        board->Info(fb);
        fb += '\n';
        return 1;
    case CMD_ShowH:     // showing history
        fb.reserve(hist.size()*5+10);
        movesRep(fb, hist);
        fb += '\n';
        return 1;
    case CMD_ShowM:     // showing valid moves
        fb.reserve(moves.size()*5+10);
        movesRep(fb, moves);
        fb += '\n';
        return 1;
    case CMD_Undo:
        if (hist.size() == 0) {
            fb = "You are at the beginning of the game.\n";
            return 0;
        }
        fb.reserve(20);
        fb += "undoing ";
        fb += hist.back()->Rep();
        fb += "...\n";
        undoRound();
        return 1;
    default:
        switch (state->GetState())
        {
        case STATE_PSetting:
            for (int i = playerType.size()-1; i >= 0; i -= 1) {
                if (cmd == playerType[i]) {
                    players.emplace_back(makePlayer(i));
                    if (pSetted()) {
                        fb.reserve(100);
                        start(fb);
                    }
                    return 1;
                }
            }
            fb = "Invalid command!\n";
            return -1;
        case STATE_Game:{
            Move * move = players[pMoveIdx()]->Decide(cmd, moves, *board, round);
            if (! move) {
                fb = "Invalid command!\n";
                return -1;
            }
            doRound(move);
            if (moves.size() == 0) {
                fb.reserve(50);
                fb += "Player ";
                fb += char(pMoveIdx()+'1');
                fb += "win.\n";
                return 0;
            }
            return 1;
        }
        
        default:
            fb = "Invalid command!\n";
            return -1;
        }
    }
}

void BoardGame::start(string & fb) {
    state->SetState(STATE_Game);
    fb += "Game started.\nPlayers:";
    for (auto & player : players) {
        fb += player->Rep();
        fb += ' ';
    }
    fb += '\n';
    resetGame();
}

bool BoardGame::pSetted() {
    return static_cast<int>(players.size()) == ePlayerCount();
}

void BoardGame::movesRep(string & m, const vector<unique_ptr<Move>> & moves) const {
    for (const unique_ptr<Move> & move : moves) {
        m += move->Rep();
        m += ' ';
    }
}

void BoardGame::doRound(Move * move) {
    move->Proc();
    move->Set(board.get());
    hist.emplace_back(move->Copy());
    round += 1;
    updateMoves();
}

int BoardGame::undoRound() {
    hist.back()->Undo();
    hist.back()->RSet(board.get());
    hist.pop_back();
    round -= 1;
    updateMoves();
    return 1;
}

int BoardGame::analyze() const {
    // TODO
    return moves.size();
}

int BoardGame::gameRound() const {
    return round/ePlayerCount();
}

int BoardGame::pMoveIdx() const {
    return round%ePlayerCount();
}

int BoardGame::updateMoves() {
    moves.clear();
    board->GetMoves(round, moves);
    if (moves.size() == 0) {
        return 0;
    }
    return 1;
}

void BoardGame::updateRMsg(string & m) const {
    m.clear();
    switch (state->GetState()) {
    case STATE_Main:
        m += "Main Menu:\n";
        break;
    case STATE_Setting:
        m += "Setting:\n";
        break;
    case STATE_PSetting:
        m.reserve(100);
        m += "Setting player ";
        m += to_string(players.size()+1);
        m += ":\n";
        break;
    case STATE_Game:
        m.reserve(400);
        board->Info(m);
        m += "\nRound ";
        m += to_string(gameRound() + 1);
        m += ",\nPlayer ";
        m += to_string(pMoveIdx() + 1);
        m += " move:";
        break;
    default:
        break;
    }
}

void BoardGame::updateCmd(string & m) const {
    state->UpdateCmds(m);
    switch(state->GetState()){
    case STATE_PSetting:
        for (const string & pt : playerType) {
            m += pt;
            m += ' ';
        }
        break;
    case STATE_Game:
        m.reserve(moves.size()*5+10);
        movesRep(m, moves);
        break;
    default:
        break;
    }
}



//  XiangQi  //
XiangQi::XiangQi() : BoardGame{} {
    board = make_unique<XQBoard>();
}

int XiangQi::ePlayerCount() const {
    return 2;
}


// main constructor
unique_ptr<BoardGame> MakeBoardGame(char type) {
    switch (type)
    {
    case 'x':
        return make_unique<XiangQi> ();
    
    default:
        return nullptr;
    }
}




