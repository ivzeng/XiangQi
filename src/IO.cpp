#include "IO.h"
#include "helpers.h"

using namespace std;

IO::IO() {}

void IO::Show(const string & m) {
    show(m);
}

int IO::Read(string & s) {
    return read(s);
}





//  IO_Std  //
CIO::CIO(istream & in, ostream & out) : IO{}, in{in}, out{out} {}

void CIO::show(const string & m) {
    out << m;
}

int CIO::read(string & s) {
    if (in.eof()) {
        return 0;
    }
    in >> s;
    lowerCase(s);
    return 1;
}
