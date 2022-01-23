#include <iostream>
#include <algorithm>
using namespace std;



int main(){
    int T;
    int p, f;
    int cnts, cntw;
    int s, w;
    cin >> T;
    while(T--){
        int ans = 0;
        cin >> p >> f;
        cin >> cnts >> cntw;
        cin >> s >> w;
        if(s < w){
            swap(s, w);
            swap(cnts, cntw);
        }
        if(p < f){
            swap(p, f);
        }
        int maxtakx;
        int ts, tw;
        ts = p / s;
        tw = 0;
        if(ts < cnts){
            maxtakx = ts;
            for (; ts >= 0; ts--){

            }
        }
    }
    return 0;
}