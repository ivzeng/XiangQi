#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>

//  Text Location Variables
#define LANGUAGE_CN 0
#define LANGUAGE_EN 1

#define MTYPE_State     0
#define MTYPE_Proc      1
#define MTYPE_Board     2
#define MTYPE_Player    3


/*************      Message/Text Classes      *************
 *  Classes storing messages/texts in certain language(s)
 * 
 *  Used for:
 *      managing language
 *      providing texts
 * 
 *********************************************************/


using MsgBlocks = std::vector<std::vector<std::vector<std::string>>>;

///****     Msg Superclass     ****///

class Msg {
    /**  Fields  **/

    protected:
    int language;
    std::vector<MsgBlocks> msgs;

    /**  Functions  **/
    virtual void init() = 0;

    // returns the number of avaliable language
    virtual int languageCount () const;

    public:

    Msg(int language = 0);
    virtual ~Msg() = 0;

    // sets specific text
    const std::string & Get(int type, int sType, int at = 0) const;
    const std::string & GetD(int type, int at = 0) const;

    // changes language
    void SetL();
};


///****  Chinese Chess Texts Subclass  ****///

class Msg_XQ : public Msg {

    /**  Functions  **/
    void init() override;

    public:

    Msg_XQ(int language);
    ~Msg_XQ();
};

#endif