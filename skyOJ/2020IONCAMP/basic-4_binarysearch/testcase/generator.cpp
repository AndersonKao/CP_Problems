#include "testlib.h"
#include <cstdlib>
#include <iostream>
#include <string>
#define MAXNUM 2e6
#define TESTMAXNUM 1e4
using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int TestNum = rnd.next(1,(int)TESTMAXNUM/2);
    cout << TestNum << endl;
    int averlen = MAXNUM / TestNum;
    string str;
    for(int i = 0; i < TestNum/3; i++){
        string teststr = "[LR]{";
        teststr+=to_string(rnd.next(2,(int)(averlen*1.75)));
        teststr+="}";
        do{
            str = rnd.next(teststr);
        }while(str == "");
        cout << rnd.next(1, (int)str.length()/2+1) << " ";
        cout << str << endl;
    }
    for(int i = TestNum/3; i<TestNum; i++){
        string teststr = "[LR]{";
        teststr+=to_string(rnd.next(2,(int)(averlen*0.25)));
        teststr+="}";
        do{
            str = rnd.next(teststr);
        }while(str == "");
        teststr = "[L]{";
        teststr+=to_string(rnd.next(2,(int)(averlen*1.5)));
        teststr+="}";
        str += rnd.next(teststr);
        cout << rnd.next(1, (int)str.length()/2+1) << " ";
        cout << str << endl;
    }
    return 0;
}