// add steps limit version
#include <iostream>
#include <string>
using namespace std;
bool solve(int d, int Jlimit,  string & str){
    int Jcounter = 0;
    int currentPos = 0;

    while(currentPos < str.length()+1){
        int move = d;
        while(currentPos + move < str.length() + 1 && str[currentPos+move-1] != 'R'){
            move--;
            if(move < 1)
                return false;
        }
        currentPos += move;
        Jcounter++;
        if(Jcounter > Jlimit)
            return false;
        // cout << "Already jumped " << Jcounter << " times.\n";
        // cout << "We moved " << move << " steps\n";
        // cout << "Now at " << str[currentPos-1] << " Postion: " << currentPos << '\n';
    }
    return true;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    int l, r, mid;
    int Jlimit;
    string str;
    cin >> T;
    while(T--){
        cin >> Jlimit;
        cin >> str;
        l = 1;
        r = str.length() + 1;
 
        // cout << l << ' ' << r << '\n';
        
        while(l < r){
            mid = (l + r) / 2;
            // cout << l << ' ' << r << ' ' << mid <<'\n';
            if(solve(mid, Jlimit,str)){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        cout << l << '\n';
    }
 
    return 0;
}

/*
6
10 LRLRRLL
10 L
10 LLR
10 RRRR
10 LLLLLL
10 R
*/
/*
12
1 LRLRRLL
2 LRLRRLL
3 LRLRRLL
2 RRRR
3 RRRR
4 RRRR
1 LLLLLL
5 LLLLLL
1 R
2 L
1 LLR
2 LLR
*/