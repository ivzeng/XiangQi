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

/**************      IO Classes      ***************
 *  Classes that handle user I/O
 * 
 *  Used for:
 *      getting commands
 *      showing messages
 * 
 **************************************************/


class BoardGame;
class Board;
class Item;
class Move;

///****     IO Superclass     ****///

class IO {

    /**   Functions  **/
    virtual void show(const std::string & m) = 0;
    virtual int read(std::string & s) = 0;

    public:
    // Constructor / Destructor
    IO();
    virtual ~IO() = 0;

    // prints string m
    void Show(const std::string & m);

    // reads a string and stores it in s
    int Read(std::string & s);
};


///****     Console IO Subclass     ****///

class CIO : public IO {
    /**   Fields  **/

    std::istream & in;
    std::ostream & out;

    /**   Functions  **/

    void show(const std::string & m);
    int read(std::string & s) override;

    public:
    CIO(std::istream & in, std::ostream & out);
    ~CIO(); 
};



#endif