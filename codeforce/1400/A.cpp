#include <iostream>
#include <string>
using namespace std;
int main(){
    int T, Len;
    cin >> T;
    string str;
    while(T--){
        cin >> Len;
        cin >> str;
        for (int i = 0; i < Len; i++){
            cout << str[Len-1];
        }
        cout << '\n';
    }
    return 0;
}