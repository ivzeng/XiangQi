#ifndef HELPERS_H
#define HELPERS_H

#include <string> 
#include <vector>
#include <queue>

//****     Path     *****//

std::string pathSep();


//****     String Operations     *****//

// managing cases
void upperCase(char & c);
void lowerCase(std::string & s);
void lowerCase(char & c);
void lowerCase(std::string & s);

//*****     Math Formulas     *****//

// returns the outcome of an exchange move
//  the result has a positive correlation with the value [to], and a negative correlation with the value [from]
double exchangeOutcome(double from, double to);

// calculates the expected outcome
double expectedOutcome(int l, std::priority_queue<double> & outcomes, double factor = 0.5);




#endif