#include "helpers.h"
#include "IO.h"
#include "BoardGame.h"

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
