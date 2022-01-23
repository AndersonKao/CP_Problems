#include <iostream>
#include <cctype>
#include <string>
#include <stringstream>
using namespace std;
#define _for(i, a, b) for(int i=(a);i<b;i++)
int main(){
    
    stringstream ss;
    int toge;
    string AA;
    int i;
    cin >> i;
    toge = i;
    ss << toge;
    AA = toge.str();

    cout << AA;

    cout << (char)24;

    return 0;
}