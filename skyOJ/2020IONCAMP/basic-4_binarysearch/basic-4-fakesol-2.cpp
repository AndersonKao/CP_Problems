// no binary search and grow from 1 version
#include <iostream>
#include <string>
using namespace std;
bool solve(int d, int Jlimit,  string & str){
    int Jcounter = 0,currentPos = 0;

    while(currentPos < str.length()+1){
        int move = 1;
        while(move <= d && currentPos + move < str.length() + 1 && str[currentPos+move-1] != 'R'){
            move++;
        }
        currentPos += move;
        Jcounter++;
        if(Jcounter > Jlimit)
            return false;
     }
    return true;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T, l, r, mid, Jlimit;
    string str;
    cin >> T;
    while(T--){
        cin >> Jlimit;
        cin >> str;
        l = 1;
        r = str.length() + 1;
        for(int i = l; i <= r; i++){
            if(solve(i, Jlimit,str)){
                cout << i << '\n';
                break;
            }
        }
    }
 
    return 0;
}