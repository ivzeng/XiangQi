#ifndef IO_H
#define IO_H

// Constances
#define MSG_State       0
#define MSG_Instruction 1
#define MSG_Error       2


#include <iostream>
#include <string>
#include <vector>
#include <map>

class BoardGame;
class Board;
class Item;
class Move;

//    IO class    //
// managing input / output
class IO {

    virtual void show(const std::string & m) = 0;
    virtual int read(std::string & s) = 0;

    public:
    IO();

    // Prints m
    void Show(const std::string & m);
    // reads a string
    int Read(std::string & s);
};

// std input / output
class CIO : public IO {
    std::istream & in;
    std::ostream & out;

    void show(const std::string & m);
    int read(std::string & s) override;

    public:
    CIO(std::istream & in, std::ostream & out);
    
};



#endif