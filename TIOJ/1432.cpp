// AC 
#include <iostream>
// #include <cstdio>
#include <algorithm>
using namespace std;
int n, m, l, r, maxW = -1;
int seq[1005];
int solve(int N); // N is the limit
int main(){

    while(cin >> n >> m){
        maxW = -1;
        if(n == 0 && m == 0)
            break;
        r = 0;
        for(int i = 0; i < n; i++){
            cin >> seq[i];
            maxW = max(seq[i], maxW);
            r += seq[i];
        }
        l = maxW;
        while(l < r){
            int mid = (l + r) / 2;
            if(solve(mid)){
                r = mid;
            }else{
                l = mid + 1;
            }
        // cout << "l: " << l << " r: " << r << '\n';
        }
        cout << l << '\n';
    }

    return 0;
}

int solve(int N){
    int log = 0, used = 0;
    for(int i = 0; i < n; i++){
        if(log + seq[i] > N){
            used++;
            log = 0;
        }   
        log += seq[i];
        if(used > m){
            return 0;
        }
    }
    return 1;
}