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
#define STATE_Setting_1 5
#define STATE_Setting_2 6
#define STATE_Setting_3 7


using CIMap = std::map<std::string, int>;

class State {
    int curState;
    std::vector<CIMap> cis;
    std::map<std::string, int> ucis;       // universal commands


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