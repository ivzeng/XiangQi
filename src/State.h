#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include <string>
#include <map>

// States Variables
#define STATE_End       0
#define STATE_Main      1
#define STATE_Setting   2
#define STATE_PSetting  3
#define STATE_Game      4
#define STATE_Training  5

/************      State Classes      *************
 *  Classes that manages states and commands
 * 
 *  Used for:
 *      handling events (commands and states)
 *      returning instruction based on the command
 *      providing helps for commands
 * 
 **************************************************/

///****     State Superclass     ****///

class State {

    /**   Fields   **/
    int curState;
    std::vector<std::map<std::string, int>> cis;    // commands at current state
    std::map<std::string, int> ucis;                // universal commands

    /**  Functions   **/

    // Initializes the class
    virtual void init();
    
    public:

    //  Constructor / Destructor
    State();
    virtual ~State() = 0;

    //  gets current state
    int GetState() const;

    //  sets current state
    void SetState(int);

    //  reads the command and returns an instruction
    int ReadCmd(const std::string & cmd);

    //  puts avaliable commands at currents state to m
    void UpdateCmds(std::string & m);

};


///****    Default State Subclass     ****///

class State_Default : public State {
    public:
    State_Default();
    ~State_Default() override;
};


#endif