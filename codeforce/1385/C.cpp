#include <iostream>
#include <algorithm>
using namespace std;

int seq[200005];

bool ifgood(int * susq, int size){
    int l = 0, r = size-1;
    // for(int i = 0; i < size; i++){
    //     cout << susq[i] << ' ';
    // }
    // cout << '\n';
    while(l != size-1 && susq[l] <= susq[l + 1])
        l++;
    while(r != 0 && susq[r] <= susq[r-1])
        r--;
    // cout << "is good l: " << l << " r: " << r << '\n';
    int L = min(l, r), R = max(l, r);
    for(int i = L ; i <= R; i++){
        if(susq[i] != susq[L])
            break;
        if(i == R)
            return true;
    }
    for(int i = 0 ; i < size; i++){
        if(susq[i] != susq[0])
            break;
        if(i == size-1)
            return true;
    }
    return false;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> seq[i];
        }
        int l = 0, r = N-1, mid;
        while(l < r){
            mid = (l + r) / 2;
            // cout << l << ' ' << r  << ' ' << mid << '\n';
            if(ifgood(seq + mid, N - mid)){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        cout << l << '\n';
    }


    return 0;
}