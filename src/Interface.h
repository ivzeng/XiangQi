#ifndef INTERFACE_H
#define INTERFACE_H

#include <memory>
#include <vector>

class IO;
class BoardGame;
class Player;

class Interface {
    protected:
    int state;         // 0: in-game, 1: main menu ...
    std::unique_ptr<BoardGame> game;
    std::vector<std::unique_ptr<Player>> players;
    virtual int proc() = 0;

    public:
    Interface(char type);
    virtual ~Interface() = 0;
    int Proc();
};

class Interface_Std : public Interface {
    std::unique_ptr<IO_Std> io;
    int proc() override;

    public:
    Interface_Std(char type);
};


#endif