#include <cstring>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#define _for(i, a, b) for (int i = (a); i < (b); i++)
int main(){
    int T;
    cin >> T;
    cin.get();
    cin.get();
    cout << "this";
    char str[T][85];
    _for(i,0,T){
        cin >> str[i];
        cin.get();
        cin.get();
        cout << str[i];
    }
    return 0;
}