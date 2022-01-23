#include "testlib.h"
#include <cstdlib>
#include <iostream>
#include <string>
#define MAXNUM 2e6
#define TESTMAXNUM 1e4
using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    cout << 10 << endl;
    for(int i = 0; i < 10; i++){
        cout << rnd.next(100,1000) << " ";
        string str = rnd.next("[R]{250000}");
        str+=rnd.next("[L]{250000}");
        cout << str << endl;

    }
    
    return 0;
}