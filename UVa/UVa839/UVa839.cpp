// AC 2021-08-06 08:12:51
/*sample input
1

0 2 0 4
0 3 0 1
1 1 1 1
2 4 4 2
1 6 3 2
*/
#include <iostream>
using namespace std;
int T;

bool balanced;
int solve(){
    int wl, dl, wr, dr;
    cin >> wl >> dl >> wr >> dr;
    if(wl == 0){
        wl = solve();
    }
    if(wr == 0){
        wr = solve();
    }
    if(wl * dl != wr * dr){
        balanced = false;
    }
    return wl + wr;
}

int main(){
    cin >> T;
    while(T--){
        
        balanced = true;
        cin.get();
        solve();
        printf((balanced ? "YES\n" : "NO\n"));
        if(T != 0){
            printf("\n");
        }
    }

    return 0;
}