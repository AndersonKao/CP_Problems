#include <bits/stdc++.h>
using namespace std;

int N;
int seq[100000];
int ans[100000] = {0}; // the length of longest increasing subsequence of subarray(0, i-1)
// the length of LIS that end in seq[i];
int main(){
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> seq[i];
        ans[i] = 1;
    }
    ans[0] = 1;
    int answer = 0;
    for (int i = 1; i < N; i++){
        for (int j = i - 1; j >= 0; j--){
            if(seq[j] < seq[i]){
                ans[i] = max(ans[i], ans[j] + 1);
            }

        }
    }
        // WA
// 1
    for (int i = 0; i < N; i++){
        answer = max(ans[i], answer);
    }
    cout << answer << endl;

// 2
//    cout << ans[N - 1] << endl;

//seq : 4 5 6 7 2
//ans : 1 2 3 4 1
    return 0;
}