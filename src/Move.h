#ifndef Move_H
#define Move_H
#include <utility>
#include <string>
#include <memory>

class BoardGame;
class Board;
class Item;


class Move {

    virtual void proc() = 0;
    virtual void undo() = 0;
    virtual void set(Board * board) = 0;
    virtual void rSet(Board * board) = 0;
    virtual std::string rep() = 0;
    virtual std::unique_ptr<Move> copy() const = 0;

    virtual double outcome() const = 0;
    virtual double pVal() const = 0;
    
    public:
    Move();
    virtual ~Move() = 0;
    void Proc();
    void Undo();
    void Set(Board * board);
    void RSet(Board * board);
    std::string Rep();
    std::unique_ptr<Move> Copy() const;

    double Outcome() const;
    double PVal() const;
};


//  XiangQi Move //
class XQPiece;

class XQMove : public Move {
    std::pair<int, int> from;
    std::pair<int, int> to;
    XQPiece * piece;
    XQPiece * captured;
    
    void proc() override;
    void undo() override;
    void set(Board * board) override;
    void rSet(Board * board) override;
    std::string rep() override;
    std::unique_ptr<Move> copy() const override;

    double outcome() const override;
    double pVal() const override;

    public:
    XQMove (const std::pair<int, int> & from, const std::pair<int, int> & to, XQPiece * target, XQPiece * captured = nullptr);
};


#endif