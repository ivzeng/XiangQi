#include "Interface.h"
#include "BoardGame.h"
#include "IO.h"
#include "State.h"


using namespace std;

Interface::Interface(char type) : game{MakeBoardGame(type)}  {
    init();
}

Interface::~Interface() {}



int Interface::Proc() {
    return handleEvents();
}

void Interface::init() {}


//  CInterface  //
CInterface::CInterface(char type) : 
    Interface{type}, io{make_unique<CIO>(cin, cout)} {}

CInterface::~CInterface() {}

int CInterface::handleEvents() {
    while (!game->Exited()) {
        string msg {};
        string cmd {};

        game->UpdateRMsg(msg);
        io->Show(msg);
        msg.clear();
        if (! io->Read(cmd)) {
            io->Show("Stopped.");
            return 0;
        }
        game->Proc(cmd, msg);
        io->Show(msg);
    }
    return 1;
}


