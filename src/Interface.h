#ifndef INTERFACE_H
#define INTERFACE_H

#include <memory>
#include <vector>

class IO;
class BoardGame;
class Player;

class Interface {
    protected:
    std::unique_ptr<BoardGame> game;

    virtual void init();
    virtual int handleEvents() = 0;

    public:
    Interface(char type);
    virtual ~Interface() = 0;
    int Proc();
};


// std interface  //
class CInterface : public Interface {
    std::unique_ptr<IO> io;
    int handleEvents() override;

    public:
    CInterface(char type);
};

#endif