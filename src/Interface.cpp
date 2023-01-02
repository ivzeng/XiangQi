#include "Interface.h"
#include "BoardGame.h"
#include "IO.h"


using namespace std;

Interface::Interface(char type) : state{1}, game{makeBoardGame(type)}  { }

Interface::~Interface() {}


int Interface::Proc() {
    return proc();
}


//  Interface_Std  //
Interface_Std::Interface_Std(char type) : Interface{type}, io{make_unique<IO_Std>(cin, cout)} {}

int Interface_Std::proc() {
    if (! game) {
        return -1;
    }
    if (game->Init() <= 0) {
        return -1;
    }
    while (!game->Stopped()) {
        const vector<string> & cmds{game->GetCmds()};

        // print instructions
        switch (game->GetState()) {

        default:
            break;
        }
        switch (game->Proc(io->Get(cmds)))
        {
        case 0:
            /* code */
            break;
        
        default:
            break;
        }
        return -2;
    }
}


