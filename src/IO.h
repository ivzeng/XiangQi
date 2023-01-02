#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include <vector>

class BoardGame;
class Board;
class Item;

//    IO class    //
// managing input / output
class IO {

    virtual int get(const std::vector<std::string> & validCmds); 
    public:
    IO();
    int Get(const std::vector<std::string> & validCmds);

    virtual void cmdInstruction(const std::vector<std::string> & cmds) = 0;
    virtual void show(const BoardGame & game, int details = 1) = 0;
    virtual void show(const std::string & s) = 0;

    // printing Messages/Instruction
    void CmdInstruction(const std::vector<std::string> & cmds);

    // Printing structure
    void Show(const BoardGame & game, int details = 1);
    void Show(const std::string & s);
};

// std input / output
class IO_Std : public IO {
    std::istream & in;
    std::ostream & out;


    int get(const std::vector<std::string> & validCmds) override;

    public:
    IO_Std(std::istream & in, std::ostream & out);
    
};



#endif