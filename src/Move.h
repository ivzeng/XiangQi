#ifndef Move_H
#define Move_H
#include <utility>
#include <string>

class BoardGame;
class Item;


class Move {

    virtual void proc() = 0;
    virtual void undo() = 0;
    virtual std::string rep() = 0;
    public:
    Move();
    virtual ~Move() = 0;
    void Proc();
    void Undo();
    std::string Rep();
};


//  XiangQi Move //
class XQPiece;

class XQMove : public Move {
    std::pair<int, int> from;
    std::pair<int, int> to;
    XQPiece * target;
    XQPiece * captured;
    
    void proc() override;
    void undo() override;
    std::string rep() override;

    public:
    XQMove (const std::pair<int, int> & from, const std::pair<int, int> & to, XQPiece * target, XQPiece * captured = nullptr);
    int Val();
};


#endif