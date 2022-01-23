#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define MAXN 50000
int MAXANS[MAXN];
int dataseq[500006];
int main(){
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for(int i = 0; i < MAXN;i++)
        MAXANS[i]  = INT32_MIN;
    int divi = 2 * sqrt(N);
    int data, i_divi;
    for(int i = 0; i < N; i++){
        cin >> data;
        i_divi = i / divi;
        dataseq[i] = data;
        MAXANS[i_divi] = max(data, MAXANS[i_divi]);
    }
    // for(int i = 0; i < N/divi + 1; i++){
    //     cout << MAXANS[i] << " ";
    // }
    // cout << "\n";
    int Q, L, R, ans;
    cin >> Q;
    while(Q--){ 
        ans = INT32_MIN;
        cin >> L >> R;
        L--;
        R--;
        if(L > R){
            int c = L;
            L = R;
            R = c;
        }
        int L_divi = L / divi, R_divi = R / divi;
        for(int i = L_divi + 1; i < R_divi; i++){
            ans = max(MAXANS[i], ans);
        }
        if(R - L <= divi){
            for(int i = L; i <=R; i++){
                ans = max(ans, dataseq[i]);
            }
        }else{
            for(int i = L; i <= (L_divi + 1) * divi; i++){
                ans = max(ans, dataseq[i]);
            }
            
            for(int i = R_divi * divi; i <= R; i++){
                ans = max(ans, dataseq[i]);
            }

        }
        cout << ans << "\n";
    }
    return 0;
}