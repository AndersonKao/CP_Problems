#include "testlib.h"
#include <string>

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int T = inf.readInt(1,1e4, "T");
    int total = 0;
    inf.readEoln();
    while(T--){
        int K = inf.readInt(1, 1e5, "K");
        inf.readSpace();
        std::string str = inf.readWord();
        if(str.length() > 5e5)
            return 22;
        else
            total += str.length();
        if(total > 5e6)
            return 23;
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}