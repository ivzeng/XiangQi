#include "Texts.h"
#include "State.h"
#include "BoardGame.h"
#include <iostream>

using namespace std;

Msg::Msg(int language) : language{language}, msgs{} {}

Msg::~Msg() {}

const string & Msg::Get(int type, int sType, int at) const {
    return msgs[language][type][sType][at];
}

const string & Msg::GetD(int type, int at) const {
    auto & s = msgs[language][type];
    return s[s.size()-1][at];
}

void Msg::SetL() {
    language = (language+1)%languageCount();
}

int Msg::languageCount() const {
    return 2;
}


// Msg_XQ

Msg_XQ::Msg_XQ(int language) : Msg{language} {
    init();
}

Msg_XQ::~Msg_XQ() {}

void Msg_XQ::init() {

    // Texts in English
    msgs = vector<MsgBlocks>(2, MsgBlocks(3));
    msgs[1][MTYPE_Board] = {
        {"", "━━", "┃", "┏", "┓", "┗", "┛", "┣", "┫", "┳", "┻", "╋"},
        {"J", "S", "G", "P", "M", "X", "B"},
        {"j", "s", "g", "p", "m", "x", "b"},
        {"red", "black"},
        {"\033[31m", "\033[30m", "\033[43m", "\033[0m"}
    };

    msgs[1][MTYPE_State] = vector<vector<string>>(6);
    msgs[1][MTYPE_State][STATE_Main] = {
        "XiangQI\nMain Menu: \n"
    };
    msgs[1][MTYPE_State][STATE_Setting] = {
        "Setting: \n"
    };
    msgs[1][MTYPE_State][STATE_PSetting] = {
        "Setting Player (", "): \n"
    };
    msgs[1][MTYPE_State][STATE_Game] = {
        "\nRound ", ",\nPlayer(", ") move:\n", "Player(", ") wins!\n"
    };

    msgs[1][MTYPE_Proc] = vector<vector<string>>(25);
    msgs[1][MTYPE_Proc][CMD_End] = {
        "Exits.\n"
    };
    msgs[1][MTYPE_Proc][CMD_ToPS] = {
        "Game started.\nPlayers:"
    };
    msgs[1][MTYPE_Proc][CMD_ResetP] = {
        "Resetted players.\n"
    };
    msgs[1][MTYPE_Proc][CMD_Undo] = {
        "You are at the beginning of the game.\n", "undoing ", "...\n"
    };
    msgs[1][MTYPE_Proc][msgs[1][MTYPE_Proc].size()-1] = {
        "Invalid command!\n"
    };


    // Texts in Chinese
    msgs[0][MTYPE_Board] = {
        {" ", "━━", "┃", " ┏", "━┓", " ┗", "━┛", " ┣", "━┫", "━┳", "━┻", "━╋"},
        {"帅", "士", "车", "炮", "马", "相", "兵"},
        {"将", "士", "车", "炮", "马", "象", "卒"},
        {"红", "黑"},
        {"\033[31m", "\033[30m", "\033[43m", "\033[0m"}
    };

    msgs[0][MTYPE_State] = vector<vector<string>>(6);
    msgs[0][MTYPE_State][STATE_Main] =      {"象棋\n主菜单:\n"};
    msgs[0][MTYPE_State][STATE_Setting] =   {"设置: \n"};
    msgs[0][MTYPE_State][STATE_PSetting] =  {"选择", "方: \n"};
    msgs[0][MTYPE_State][STATE_Game] =      {"\n回合 ", ", \n", "方回合:", "", "方获胜!\n"};

    msgs[0][MTYPE_Proc] = vector<vector<string>>(25);
    msgs[0][MTYPE_Proc][CMD_End] =          {"退出。\n"};
    msgs[0][MTYPE_Proc][CMD_ToPS] =         {"对局开始...\n双方:"};
    msgs[0][MTYPE_Proc][CMD_ResetP] =       {"双方已重置。\n"};
    msgs[0][MTYPE_Proc][CMD_Undo] =         {"重做失败: 未有走棋。\n", "返回上一步[", "]...\n"};
    msgs[0][MTYPE_Proc][msgs[0][MTYPE_Proc].size()-1] = {"无效指令, 请重试。\n"};
}


