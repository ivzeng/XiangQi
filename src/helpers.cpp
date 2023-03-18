#include "helpers.h"
#include "IO.h"
#include "BoardGame.h"
#include <math.h>

using namespace std;


void upperCase(char & c) {
    if ('a' <= c && 'z' >= c) {
        c += 'A' - 'a';
    }
}
void upperCase(std::string & s) {
    for (char & c : s) {
        upperCase(c);
    }
}
void lowerCase(char & c) {
    if ('A' <= c && 'Z' >= c) {
        c += 'a' - 'A';
    }
}
void lowerCase(std::string & s){
    for (char & c : s) {
        lowerCase(c);
    }
}


double exchangeOutcome(double valueFrom, double valueTo) {
    return valueTo - pow(valueFrom, 2)*pow(valueTo, 0.5)/1000;
}

double expectedOutcome(
    int l, std::priority_queue<double> & outcomes, double factor
){
    double res = 0;
    double remain = 1;
    if ((int)outcomes.size() < l) {
        l = outcomes.size();
    }
    while (l != 1) {
        res +=(double)outcomes.top()*remain*factor;
        outcomes.pop();
        remain *= (1-factor);
        l -= 1;
    }
    res += outcomes.top()*remain;
    return res;
}
