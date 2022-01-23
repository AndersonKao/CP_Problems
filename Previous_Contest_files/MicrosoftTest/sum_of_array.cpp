#include <iostream>
using namespace std;
int main(){
    int T,adding,Ans = 0;
    cin >> T;
    while(T--){
        cin >> adding;
        Ans += adding;
    }
    cout << Ans;
    return 0;
}