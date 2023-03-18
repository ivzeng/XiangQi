#ifndef INTERFACE_H
#define INTERFACE_H

#include <memory>
#include <vector>


/**********      Interface Classes      ************
 *  Classes that handle BoardGame-IO interactions
 * 
 *  Used for:
 *      transmitting messages/commands bewteen IO 
 *        and BoardGame Class
 * 
 **************************************************/

class IO;
class BoardGame;
class Player;

///****     Interface Superclass     ****///
class Interface {
    /**   Fields   **/
    protected:
    std::unique_ptr<BoardGame> game;

    /**   Functions   **/
    
    virtual void init();

    virtual int handleEvents() = 0;

    public:

    // Construction / Destruction
    Interface(char type);
    virtual ~Interface() = 0;

    // Processes the Game
    int Proc();
};


///****     Console Interface     ****///
class CInterface : public Interface {
    /**   Fields   **/
    std::unique_ptr<IO> io;

    /**   Functions   **/
    int handleEvents() override;

    public:
    CInterface(char type);
    ~CInterface() override; 
};

#endif