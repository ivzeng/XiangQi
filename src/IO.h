#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include <vector>

class Game;
class Board;
class Piece;

//    IO class    //
// managing input / output
class IO {

    public:
    IO();
};

// std input / output
class IO_Std : public IO {

    std::string getString(std::istream & in);
    public:
    IO_Std();
    
    // getting inputs
    int readCmd(std::istream & in, const std::vector<std::string> & cmd);
    int readCmd(std::istream & in, const std::vector<char> & cmd);
    int readPT(std::istream & in, const std::vector<std::string> & cmd);

    // printing Messages/Instruction
    void cmdInstruction(std::ostream & out);
    void PTInstruction(std::ostream & out);

    // Printing structure
    void print(std::ostream & out, const Game & game);
};

// Printing structure
std::ostream & operator<<(std::ostream & out, const Piece & piece);
std::ostream & operator<<(std::ostream & out, const Board & board);
std::ostream & operator<<(std::ostream & out, const Game & game);


#endif