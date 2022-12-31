#include "Interface.h"
#include "BoardGame.h"
#include "IO.h"


using namespace std;

Interface::Interface(char type) : state{1}, game{makeBoardGame(type)}, players{}  { }

Interface::~Interface() {}


int Interface::Proc() {
    return proc();
}


//  Interface_Std  //
Interface_Std::Interface_Std(char type) : Interface{type}, io{make_unique<IO_Std>()} {}

int Interface_Std::proc() {
    if (! game) {
        return -1;
    }
    game->Init();
    while (io->readCmd(cin, {"play"}) == -1) {
        io->PTInstruction(cout);
    }
    // TODO
}


