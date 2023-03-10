#include "State.h"
#include "BoardGame.h"
#include <iostream>

using namespace std;


/**   State   ***/
State::State() : curState{0}, cis{}, ucis{} {
    init();
}

State::~State() {}

void State::init() {
    curState = 1;
    cis = vector<map<string, int>>(5);
    cis[STATE_End] = {};
    cis[STATE_Main] = {{"end", CMD_End}, {"showb", CMD_ShowB}, {"set", CMD_ToS}, {"play", CMD_ToPS}, {"resetp", CMD_ResetP}};
    cis[STATE_Setting] = {{"back", CMD_ToMain}, {"setl", CMD_SetL}};
    cis[STATE_PSetting] = {{"back", CMD_ToMain}};
    cis[STATE_Game] = {{"end", CMD_ToMain}, {"hist", CMD_ShowH}, {"moves", CMD_ShowM}, {"undo", CMD_Undo}};
    ucis = {{"showc", CMD_ShowC}};
}

int State::GetState() const {
    return curState;
}

void State::SetState(int ns) {
    curState = ns;
}

int State::ReadCmd(const string & cmd) {
    if (cis[curState].find(cmd) != cis[curState].end()) {
        return cis[curState][cmd];
    }
    if (ucis.find(cmd) != ucis.end()) {
        return ucis[cmd];
    }
    return -1;
}

void State::UpdateCmds(string & m) {
    for (pair<string, int> uCmd: ucis) {
        m += uCmd.first;
        m += ' ';
    }
    for (pair<string, int> cmd : cis[curState]) {
        m += cmd.first;
        m += ' ';
    }
}


/***   State_Default   ***/
State_Default::State_Default() : State{} {}
State_Default::~State_Default() {}