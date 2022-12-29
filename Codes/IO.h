#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>


// Input
bool readCmd(std::istream & in, std::string & cmd);
bool readPT(std::istream & in, int pt[2]);
bool readMove(std::istream & in, std::string & move);

//      Messages/Instruction        //
void cmdInstruction(std::ostream & out);
void PTInstruction(std::ostream & out);


#endif