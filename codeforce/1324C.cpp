// AC Jul/18/2020 15:05UTC+8
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
bool flag = false;
// bool visited[200005];

bool solve(int d, string & str){
    int counter = 0;
    int pos = 1;
    while(pos <= str.length()+1){
        counter++;
        if(counter > d)
            return false;
        if(pos == str.length()+1)
            break;
        if(str[pos-1] == 'R'){
            counter = 0;
        }
        pos++;
    }
    return true;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    int l, r, mid;
    string str;
    cin >> T;
    while(T--){
        cin >> str;
        l = 1;
        r = str.length() + 1;

        // cout << l << ' ' << r << '\n';
        
        while(l < r){
            mid = (l + r) / 2;
            // cout << l << ' ' << r << ' ' << mid <<'\n';
            if(solve(mid, str)){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        cout << l << '\n';
    }

    return 0;
}