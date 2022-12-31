#include "IO.h"
#include "BoardGame.h"
#include "Board.h"
#include "Piece.h"
#include "helpers.h"

using namespace std;

IO::IO () {}

IO_Std::IO_Std() : IO{} {}

string IO_Std::getString(istream & in) {
    string s = "";
    in >> s;
    return s;
}

int IO_Std::readCmd(istream & in, const vector<string> & cmd) {
    string inCmd{getString(in)};
    lowerCase(inCmd);
    for (int i = cmd.size()-1; i >= 0; i -= 1) {
        if (inCmd == cmd[i]) return i;
    }
    return -1;
}

int IO_Std::readCmd(istream & in, const vector<char> & cmd) {
    char inCmd{getString(in)[0]};
    lowerCase(inCmd);
    for (int i = cmd.size()-1; i >= 0; i -= 1) {
        if (inCmd == cmd[i]) return i;
    }
    return -1;
}

int IO_Std::readPT(istream & in, const vector<string> & cmd){
    string inCmd {getString(in)};
    char type {inCmd[0]};
    char level {inCmd[inCmd.size()-1]};
    lowerCase(type);
    inCmd = "" + type;
    if ('0' <= level && level <= cmd[cmd.size()-1][1]) {
        inCmd += level;
    }
    for (int i = cmd.size()-1; i >= 0; i -= 1) {
        if (inCmd == cmd[i]) return i;
    }
    return -1;
}


void IO_Std::print(std::ostream & out, const Game & game) {
    out << game;
}


ostream & operator<<(ostream & out, const Item & item){
    out << item.Rep();
    return out;
}


ostream & operator<<(ostream & out, const Board & board){
    for (int y = 9; y >= 0; y -= 1) {
        out << y << ' ';
        for (int x = 0; x < 9; x += 1) {
            out << board.get(x, y) ? board.get(x, y)->rep() : '-'  << ' ';
        }
        out << endl;
    }
    out << "  ";
    for (int x = 0; x < 9; x += 1) {
        out << char(x + 'a') << ' ';
    }
    return out;
}

ostream & operator<<(ostream & out, const Game & game) {
    return out;
}