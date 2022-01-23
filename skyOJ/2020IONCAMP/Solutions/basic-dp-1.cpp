#include <iostream>
#include <algorithm>
// #include <cstring>
using namespace std;
int N, K;
int seq[100005];
int ans[100005] = {0};
int dp(int index){
    if(index < 0)
        return 0;
    if(ans[index] != 0)
        return ans[index];
    ans[index] = max(dp(index-1), dp(index-K-1) + seq[index]);


    
    return ans[index];
}
int main(){
    cin >> N >> K;
    for(int i = 0; i < N; i++){
        cin >> seq[i];
    }
    dp(N-1);
    // for(int i = 0; i < N; i++){
    //     cout << seq[i] << " ";
    // }
    // cout << '\n';
    
    // for(int i = 0; i < N; i++){
    //     cout << ans[i] << " ";
    // }
    // cout << '\n';

    cout << ans[N-1] << '\n';










    return 0;
}