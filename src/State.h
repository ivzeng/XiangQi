#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include <string>
#include <map>

#define STATE_End       0
#define STATE_Main      1
#define STATE_Setting   2
#define STATE_PSetting  3
#define STATE_Game      4

class State {
    int curState;
    std::vector<std::map<std::string, int>> cmds;
    std::map<std::string, int> uCmds;       // universal commands


    virtual void init();
    
    public:
    State();
    virtual ~State() = 0;
    int GetState() const;
    void SetState(int);
    int ReadCmd(const std::string & cmd);
    void UpdateCmds(std::string & m);

};

class State_Default : public State {
    public:
    State_Default();
};

#endif