#include "Game.h"
#include "IO.h"

using namespace std;

int main () {
    int score [2] {0};
    bool isRunning = true;
    Game game{};
    while (isRunning){
        string cmd = "";
        while (!readCmd(cin, cmd)){
            cmdInstruction(cout);
        }
        if (cmd == "end") {
            isRunning = false;
            break;
        }
        int playerTypes[2] = {0, 0};
        while (!readPT(cin, playerTypes)) {
            PTInstruction(cout);
        }
        game.init(playerTypes);
        while (!game.end()) {
            game.process();
        }

    }

}