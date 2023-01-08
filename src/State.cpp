#include "State.h"
#include "BoardGame.h"

using namespace std;

State::State() : curState{0}, cmds{}, uCmds{} {
    init();
}

State::~State() {}

void State::init() {
    curState = 1;
    cmds = vector<map<string, int>>(5);
    cmds[STATE_End] = {};
    cmds[STATE_Main] = {{"end", CMD_End}, {"showb", CMD_ShowB}, {"set", CMD_ToS}, {"play", CMD_ToPS}, {"resetp", CMD_ResetP}};
    cmds[STATE_Setting] = {{"back", CMD_ToMain}};
    cmds[STATE_PSetting] = {{"back", CMD_ToMain}};
    cmds[STATE_Game] = {{"end", CMD_ToMain}, {"hist", CMD_ShowH}, {"moves", CMD_ShowM}, {"undo", CMD_Undo}};
    
    uCmds = {{"showc", CMD_ShowC}};
}

int State::GetState() const {
    return curState;
}

void State::SetState(int ns) {
    curState = ns;
}

int State::ReadCmd(const string & cmd) {
    if (cmds[curState].find(cmd) != cmds[curState].end()) {
        return cmds[curState][cmd];
    }
    if (uCmds.find(cmd) != uCmds.end()) {
        return uCmds[cmd];
    }
    return -1;
}

void State::UpdateCmds(string & m) {
    for (pair<string, int> uCmd: uCmds) {
        m += uCmd.first;
        m += ' ';
    }
    for (pair<string, int> cmd : cmds[curState]) {
        m += cmd.first;
        m += ' ';
    }
}

State_Default::State_Default() : State{} {}