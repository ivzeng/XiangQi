#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>

#define LANGUAGE_CN 0
#define LANGUAGE_EN 1

#define MTYPE_State 0
#define MTYPE_Proc  1
#define MTYPE_Board 2


using MsgBlocks = std::vector<std::vector<std::vector<std::string>>>;

class Msg {
    protected:
    int language;
    std::vector<MsgBlocks> msgs;
    virtual void init() = 0;
    virtual int lc () const;
    public:
    Msg();
    virtual ~Msg() = 0;
    const std::string & Get(int type, int sType, int at = 0) const;
    const std::string & GetD(int type, int at = 0) const;

    void SetL();
};

class Msg_XQ : public Msg {
    void init() override;

    public:
    Msg_XQ();
};

#endif