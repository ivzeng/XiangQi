#include "Player.h"
#include "BoardGame.h"
#include "Move.h"
#include "Board.h"
#include "helpers.h"
#include <iostream>
#include <algorithm>
#include <sys/stat.h>
#include <fstream>

using namespace std;


/**   Player   **/

Player::Player() {}

Player::~Player() {}

string Player::Rep() const {
    return rep();
}

int Player::Type() const {
    return type();
}

Move * Player::Decide(
    Board * board, int round,
    const string & cmd,
    vector<unique_ptr<Move>> & moves
) {
    return decide(board, round, cmd, moves);
}

void Player::initMovesEPayoff(
    const vector<unique_ptr<Move>> & moves,
    vector<pair<double, Move *>> & movesEPayoff
) const {
    int ml = moves.size();
    movesEPayoff = vector<pair<double, Move *>>(ml, pair<double, Move *>{0, nullptr});
    for (int i = 0; i < ml; i += 1){
        movesEPayoff[i].second = moves[i].get();
    }
}

double Player::eOutcome(
    Board * board, int round
) {
        return board->Outcome(round, 0);
}

double Player::eOutcome(
    int l, double factor,
    const vector<pair<double, Move *>> & movesEPayoff
) const {
    
    // calculate expected outcome
    double res = 0;
    double remain = 1;
    if ((int)movesEPayoff.size() <= l) {
        l = movesEPayoff.size()-1;
    }
    for (int i = 0; i < l; i += 1) {
        res += (double) movesEPayoff[i].first*remain*factor;
        remain *= (1-factor);
    }
    res += (double) movesEPayoff[l].first*remain;
    return res;
}

double Player::dfsMovesAnalysis(
    Board * board, int round, int depth,
    vector<pair<double, Move *>> & movesEPayoff
) {
    int n = movesEPayoff.size();

    // case: there is no avaliable move, the opponent wins
    if (n == 0) {
        return -1000;
    }

    // analyze the expected payoff of each move and store it into movesEPayoff
    round += 1;
    depth /= n;
    for (pair<double, Move *> & move : movesEPayoff) {
        move.second->Proc();
        move.second->Set(board);

        if (depth <= 1) {
            move.first = eOutcome(board, round);
        }
        else {
            vector<unique_ptr<Move>> nextMoves{};
            vector<pair<double, Move *>> nextMovesEPayoff{};
            board->GetMoves(round, nextMoves);
            initMovesEPayoff(nextMoves, nextMovesEPayoff);
            move.first = dfsMovesAnalysis(board, round, depth, nextMovesEPayoff);
        }
        move.second->Undo();
        move.second->RSet(board);
    }

    // sort movesEPayoff by payoff into accending order
    sort(
        movesEPayoff.begin(), movesEPayoff.end(),
        [] (const pair<double, Move *> & m1, const pair<double, Move *> & m2) -> bool {
            return m1.first < m2.first;
        }
    );

    /*
    #ifdef DEBUG
    cout << "Round " << round - 1 << endl; 
    for (const auto & m : movesEPayoff) {
        cout << m.second->Rep() << " " << m.first << endl; 
    }
    cout << endl;
    #endif
    */

    // calculates the overall outcome
    int l = (n <= 1) ? (n+1)/2 : (n+3)/4;
    double factor = (n <= 1) ? (double)0.4 : (double)0.7;
    return -eOutcome(l, factor, movesEPayoff);
}

double Player::analyzeMoves(
    Board * board, int round, vector<pair<double, Move *>> & movesEPayoff
) {
    return dfsMovesAnalysis(board, round, operations(), movesEPayoff);
}

void Player::storeInfo(
    Board * board, int round, double expectedPayoff,
    const vector<pair<double, Move *>> & movesEPayoff
) {}

Move * Player::selectMove(
    const std::vector<std::pair<double, Move *>> & movesEPayoff
) const {
    return movesEPayoff[0].second;
}

Move * Player::decideMove(
    Board * board, int round, const vector<unique_ptr<Move>> & moves
) {
    if (moves.size() == 0) {
        return nullptr;
    }
    else if (moves.size() == 1) {
        return moves[0].get();
    }
    vector<pair<double, Move *>> movesEPayoff{};
    initMovesEPayoff(moves, movesEPayoff);
    double expectedPayoff = analyzeMoves(board, round, movesEPayoff);
    storeInfo(board, round, expectedPayoff, movesEPayoff);
    #ifdef DEBUG
    cout << "Round " << round << endl; 
    for (const auto & m : movesEPayoff) {
        cout << m.second->Rep() << " " << m.first << endl; 
    }
    cout << endl;
    #endif
    return selectMove(movesEPayoff);
}

int Player::operations() const {
    return 50000;
}


/**    Human    **/
Human::Human() : Player{} {}

Human::~Human() {}

std::string Human::rep() const {
    return "human";
}

int Human::type() const {
    return PLAYER_HU;
}

Move * Human::decide(
    Board * board, int round,
    const string & cmd,
    vector<unique_ptr<Move>> & moves
) {
    if (cmd == "hint") {
        return decideMove(board, round, moves);
    }
    for (auto & move : moves) {
        if (move->Rep() == cmd) {
            return move.get();
        }
    }
    return nullptr;
}


/***  Computer Players   ***/
Computer::Computer() : Player{} {}
Computer::~Computer() {}

Move * Computer::decide(
    Board * board, int round,
    const string & cmd,
    vector<unique_ptr<Move>> & moves
) {
    if (cmd != "m" && cmd != "") {
        return nullptr;
    }
    return decideMove(board, round, moves);
}

Move * Computer::rSelectMove(
    const vector<pair<double, Move *>> & movesEPayoff, float prob, float range
) const {
    int l = movesEPayoff.size()*range;
    if (l == 0) {
        return movesEPayoff[0].second;
    }
    int i = 0;
    int ub = prob*RAND_MAX;
    while (i < l - 1) {
        int d = rand();
        if (d < ub) {
            return movesEPayoff[i].second;
        }
        i += 1;
    }
    return movesEPayoff[i].second;
}

/**   Computer 0   **/
Computer0::Computer0() : Computer{} {}
Computer0::~Computer0() {}

string Computer0::rep() const {
    return "computer0";
}

int Computer0::type() const {
    return PLAYER_C0;
}


/**  Computer 1  **/
Computer1::Computer1() : Computer{} {}
Computer1::~Computer1() {}

string Computer1::rep() const{
    return "computer1";
}

int Computer1::type() const {
    return PLAYER_C1;
}

int Computer1::operations() const {
    return 5000000;
}

/**  Computer 2  **/
Computer2::Computer2() : Computer{} {}
Computer2::~Computer2() {}

string Computer2::rep() const {
    return "computer2";
}

int Computer2::type() const {
    return PLAYER_C2;
}

int Computer2::operations() const {
    return 150000;
}

double Computer2::eOutcome(Board * board, int round) {
    return board->Outcome(round, 1);
}

/**  Computer 3  **/
Computer3::Computer3() : Computer{} {}

Computer3::~Computer3() {}

string Computer3::rep() const {
    return "computer3";
}

int Computer3::type() const {
    return PLAYER_C3;
}

int Computer3::operations() const {
    return 150000;
}

double Computer3::eOutcome(
    Board * board, int round
) {
    return board->Outcome(round, 1);
}

Move * Computer3::selectMove(
    const vector<pair<double, Move *>> & movesEPayoff
) const {
    return rSelectMove(movesEPayoff);
}

/**  Computer 4  **/
int Computer4::dCount = 0;
map<string, double> Computer4::etpo{};

//queue<string> Computer4::timePoints{};
//unordered_map<string, double> Computer4::btpo{};


Computer4::Computer4() : Computer{} {
    if (dCount == 0) init();
    dCount += 1;
}

Computer4::~Computer4() {
    dCount -= 1;
    if (dCount == 0)
        updateTpoFile();
}

string Computer4::rep() const {
    return "computer4";
}

int Computer4::type() const {
    return PLAYER_C4;
}

int Computer4::operations() const {
    return 4000000;
}

double Computer4::eOutcome(
    Board * board, int round
) {
    string boardInStr{board->ToString(round)};
    if (etpo.find(boardInStr) != etpo.end()) {
        return etpo[boardInStr];
    }
    /*
    if (btpo.find(boardInStr) == btpo.end()) {
        timePoints.push(boardInStr);
        btpo[boardInStr] = board->Outcome(round, 0);
        if (timePoints.size() > 10000000) {
            btpo.erase(timePoints.front());
            timePoints.pop();
        }
    }
    return btpo[boardInStr];
    */
    return board->Outcome(round, 0);
}

void Computer4::storeInfo(
    Board * board, int round, double expectedPayoff, const vector<pair<double, Move *>> & movesEPayoff
) {
    for (const pair<double, Move *> & move : movesEPayoff) {
        move.second->Proc();
        move.second->Set(board);
        string boardInStr = board->ToString(round+1);
        etpo[boardInStr] = expectedPayoff;
        move.second->Undo();
        move.second->RSet(board);
    }
    string boardInStr = board->ToString(round);
    etpo[boardInStr] = expectedPayoff;
    #ifdef DEBUG
    cout << "etop size: " << etpo.size() << endl;
    #endif
}

Move * Computer4::selectMove(
    const vector<pair<double, Move *>> & movesEPayoff
) const {
    return rSelectMove(movesEPayoff, 0.6);
}


void Computer4::init() {
    initTpoFile();
    updateTpo();
}

void Computer4::initTpoFile() {
    // create the directory if it does not exist
    const string dir(dataDir());
    struct stat sb;
    if (stat(dir.c_str(), &sb) != 0) {
        if(mkdir(dir.c_str(), 0777) == -1) {
            #ifdef DEBUG
            cerr << "Error: initTpoFile()" << endl;
            #endif
        }
    }

    // create the file if it does not exist
    fstream fs;
    fs.open(fileDir(), std::ios::out | std::ios::app);
    fs.close();
}

void Computer4::updateTpo() {
    fstream fs;
    fs.open(fileDir(), std::ios::in);
    while(fs.peek() != EOF) {
        char timePoint[33];
        fs.get(timePoint, 33, EOF);
        string tp{timePoint};
        double outcome;
        fs >> outcome;
        etpo[tp] = outcome;
        fs.get();
    }
    fs.close();
}

void Computer4::updateTpoFile() {
    ofstream fs;
    fs.open(fileDir(), std::ios::out);
    fs.close();
    fs.open(fileDir(), ios::app);
    #ifdef DEBUG
    cout << "Updating tpo file...\n" << endl;
    #endif
    for (const pair<const string, double> & tpo : etpo) {
        fs << tpo.first << ' ' << tpo.second << '\n';
    }
    etpo.clear();
    /*
    timePoints = queue<string>{};
    btpo.clear();
    */
}

string Computer4::fileDir() {
    return dataDir() + pathSep() + fileName();
}

string Computer4::dataDir() {
    return "data";
}

string Computer4::fileName() {
    return "c4.tpo";
}


/***  Other Functions  ***/
unique_ptr<Player> makePlayer(int type) {
    switch (type)
    {
    case 0:
        return make_unique<Human>();
    case 1:
        return make_unique<Computer0>();
    case 2:
        return make_unique<Computer1>();
    case 3:
        return make_unique<Computer2>();
    case 4:
        return make_unique<Computer3>();
    case 5:
        return make_unique<Computer4>();
    
    default:
        return nullptr;
    }
}