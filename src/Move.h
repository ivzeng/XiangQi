#ifndef Move_H
#define Move_H
#include <utility>
#include <string>
#include <memory>

class BoardGame;
class Board;
class Item;


class Move {
    /**   Fields   **/

    /**   Functions   **/
    virtual void proc() = 0;
    virtual void undo() = 0;
    virtual void set(Board * board) = 0;
    virtual void rSet(Board * board) = 0;
    virtual std::string rep() = 0;
    virtual std::unique_ptr<Move> copy() const = 0;
    virtual double outcome() const = 0;
    virtual double getPiece() const = 0;
    virtual std::vector<Item *> items() const = 0;

    public:
    // constructor / destructor
    Move();
    virtual ~Move() = 0;

    // processes the move
    void Proc();

    // undos the move
    void Undo();

    // sets the board
    void Set(Board * board);

    // resets the board
    void RSet(Board * board);

    // returns the string representation of the move
    std::string Rep();

    // makes a copy
    std::unique_ptr<Move> Copy() const;

    // returns the outcome of the move
    double Outcome() const;

    // get the items
    std::vector<Item *> Items() const;

};


//  XiangQi Move //
class XQPiece;

class XQMove : public Move {
    std::pair<int, int> from;
    std::pair<int, int> to;
    XQPiece * piece;
    XQPiece * target;
    
    void proc() override;
    void undo() override;
    void set(Board * board) override;
    void rSet(Board * board) override;
    std::string rep() override;
    std::unique_ptr<Move> copy() const override;
    double outcome() const override;
    std::vector<Item *> items() const override;

    public:
    XQMove (const std::pair<int, int> & from, const std::pair<int, int> & to, XQPiece * target, XQPiece * captured = nullptr);
};


#endif