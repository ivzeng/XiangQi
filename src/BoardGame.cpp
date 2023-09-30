#include "BoardGame.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Item.h"
#include "State.h"
#include "Texts.h"
#include <iostream>

using namespace std;

BoardGame::BoardGame() : 
    mode{1}, state{nullptr}, msg{nullptr}, playerType{}, scores{}, board{},
    round {0}, moves{}, hist{}, players{} {}

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
    playerType.reserve(6);
    playerType.emplace_back("h");
    playerType.emplace_back("c0");
    playerType.emplace_back("c1");
    playerType.emplace_back("c2");
    playerType.emplace_back("c3");
    playerType.emplace_back("c4");
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
        fb = msg->Get(MTYPE_Proc, CMD_End);
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
            mode = 1;
            state->SetState(STATE_PSetting);
        }
        return 1;
    case CMD_ResetP:    // resetting players
        players.clear();
        fb = msg->Get(MTYPE_Proc, CMD_ResetP);
        return 1;
    case CMD_SetL:
        msg->SetL();
        return 1;
    case CMD_Tr:
        if (pSetted()) {
            fb.reserve(100);
            startTr(fb);
        }
        else {
            mode = 2;
            state->SetState(STATE_PSetting);
        }
        return 1;
    case CMD_ShowC:
        fb.reserve(200);
        updateCmd(fb);
        fb += '\n';
        return 1;
    case CMD_ShowB:     // showing board
        fb.reserve(600);
        board->Info(fb, *msg);
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
            fb = msg->Get(MTYPE_Proc, CMD_Undo);
            return 0;
        }
        
        fb.reserve(20);
        fb += msg->Get(MTYPE_Proc, CMD_Undo, 1);
        fb += hist.back()->Rep();
        fb += msg->Get(MTYPE_Proc, CMD_Undo, 2);
        
        undoRound();
        return 1;
    default:
        switch (state->GetState())
        {
        case STATE_PSetting:
        // setting player
            for (int i = playerType.size()-1; i >= 0; i -= 1) {
                if (cmd == playerType[i]) {
                    players.emplace_back(makePlayer(i));
                    if (pSetted()) {
                        fb.reserve(100);
                        switch (mode)
                        {
                        case 2:
                            startTr(fb);
                            break;
                        default:
                            start(fb);
                            break;
                        }
                    }
                    return 1;
                }
            }
            fb = msg->GetD(MTYPE_Proc, 0);
            return -1;
        case STATE_Game: {
            // making move
            Move * move = players[pMoveIdx()]->Decide(board.get(), round, cmd, moves);
            if (! move) {
                fb = msg->GetD(MTYPE_Proc, 0);
                return -1;
            }
            fb += move->Rep();
            fb += '\n';
            doRound(move);
            if (moves.size() == 0) {
                fb.reserve(50);
                fb += msg->Get(MTYPE_State, STATE_Game, 3);
                fb += msg->Get(MTYPE_Board, 3, 1-pMoveIdx());
                fb += msg->Get(MTYPE_State, STATE_Game, 4);
                return 0;
            }
            return 1;
        }

        case STATE_Training:
        {
            int n = stoi(cmd);
            return train(n,fb);
        }

        default:
        // warning invalid cmd
            fb = msg->GetD(MTYPE_Proc, 0);
            return -1;
        }
    }
}

void BoardGame::start(string & fb) {
    state->SetState(STATE_Game);
    fb += msg->Get(MTYPE_Proc, CMD_ToPS, 0);
    showPlayers(fb);
    resetGame();
}

void BoardGame::startTr(string & fb){
    state->SetState(STATE_Training);
    fb += msg->Get(MTYPE_Proc, CMD_Tr, 0);
    showPlayers(fb);
}


int BoardGame::train(int n, string & fb) {
    fb.reserve(n*1000);
    fb += msg->Get(MTYPE_State, STATE_Training, 2);
    while (n > 0) {
        resetGame();
        fb += to_string(n) + ":\n";
        while (moves.size() != 0 && round <= 20) {
            Move * move = players[pMoveIdx()]->Decide(board.get(), round, "m", moves);
            if (! move) {
                fb = msg->GetD(MTYPE_Proc, 1);
                resetPlayers();
                state->SetState(STATE_Main);
                return -1;
            }
            fb += move->Rep() + " ";
            doRound(move);
        }
        fb += '\n';
        n -= 1;
    }
    fb += msg->Get(MTYPE_State, STATE_Training, 3);
    resetPlayers();
    state->SetState(STATE_Main);
    return 1;
}

bool BoardGame::pSetted() {
    return static_cast<int>(players.size()) == ePlayerCount();
}

void BoardGame::showPlayers(string & fb) const {
    fb += msg->Get(MTYPE_Proc, CMD_ToPS, 1);
    for (const unique_ptr<Player> & p : players) {
        fb += msg->Get(MTYPE_Player, p->Type());
        fb += '\n';
    }
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
        m += msg->Get(MTYPE_State, STATE_Main);
        break;
    case STATE_Setting:
        m += msg->Get(MTYPE_State, STATE_Setting);
        break;
    case STATE_PSetting:
        m.reserve(100);
        m += msg->Get(MTYPE_State, STATE_PSetting);
        m += msg->Get(MTYPE_Board, 3, players.size());
        m += msg->Get(MTYPE_State, STATE_PSetting, 1);
        break;
    case STATE_Game:
        board->Info(m, *msg);
        m += msg->Get(MTYPE_State, STATE_Game, 0);
        m += to_string(gameRound() + 1);
        m += msg->Get(MTYPE_State, STATE_Game, 1);
        m += msg->Get(MTYPE_Board, 3, pMoveIdx());
        m += msg->Get(MTYPE_State, STATE_Game, 2);
        break;
    case STATE_Training:
        m += msg->Get(MTYPE_State, STATE_Training, 0);
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
    case STATE_Training:
        m.reserve(50);
        m += msg->Get(MTYPE_State, STATE_Training, 1);
        break;
    default:
        break;
    }
}



//  XiangQi  //
XiangQi::XiangQi() : BoardGame{} {
    init();
}

int XiangQi::ePlayerCount() const {
    return 2;
}


void XiangQi::init() {
    BoardGame::init();
    msg = make_unique<Msg_XQ>(INIT_LANGUAGE-1);
    board = make_unique<XQBoard>();
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




