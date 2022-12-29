#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>

class Move;
class Board;

//      Piece Class     //
// handles move-searching; 
// is one of the following:
//   Jiang | Shi | Ju | Pao | Ma | Xiang | Bing
class Piece {
    protected:
    int status;
    int colour;
    std::pair<int,int> pos;

    // functions
    virtual int val() = 0;

    public:

    Piece(int colour, const std::pair<int,int> & pos);
    virtual ~Piece() = 0;

    void setStatus();
    int value();
    
};

class Jiang : public Piece {
    public:
    Jiang(int colour, const std::pair<int,int> & pos);
    int val() override;
};

class Shi : public Piece {
    public:
    Shi(int colour, const std::pair<int,int> & pos);
    int val() override;
};

class Ju : public Piece {
    public:
    Ju(int colour, const std::pair<int,int> & pos);
    int val() override;
};

class Pao : public Piece {
    public:
    Pao(int colour, const std::pair<int,int> & pos);
    int val() override;
};

class Xiang : public Piece {
    public:
    Xiang(int colour, const std::pair<int,int> & pos);
    int val() override;
};

class Ma : public Piece {
    public:
    Ma(int colour, const std::pair<int,int> & pos);
    int val() override;
};

class Bing : public Piece {
    public:
    Bing(int colour, const std::pair<int,int> & pos);
    int val() override;
};

#endif