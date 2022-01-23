// AC Mar/12/2020 21:01UTC+8
#include <iostream>
#include <algorithm>
using namespace std;

int seq[100005];
int ans[100005] = {1};
int main(){
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> seq[i];
    }
    for(int i = 1; i <= N; i++){
        // for(int j = 1; j < i; j++){
            if(seq[i-1] <= seq[i] && i > 1) 
                ans[i] = ans[i-1] + 1;
            else
                ans[i] = 1;
        // }
    }
    int ANS = INT32_MIN;
    for(int i = 1; i <= N; i++)
        ANS = max(ans[i], ANS);
    cout << ANS << '\n';
    return 0;
}