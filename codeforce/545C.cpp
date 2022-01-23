// AC Sep/08/2020 11:14UTC+8
#include <iostream>
using namespace std;
int pos[100005];
int h[100005];
int ans[100005][3]= {0}; // 0 for not fell, 1 for left, 2 for right
int main(){

    int N;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> pos[i] >> h[i];
    }
    ans[0][0] = 0;
    ans[0][1] = 1;
    ans[0][2] = 1;
    for (int i = 1; i < N - 1; i++){
        // stand
        ans[i][0] = max(ans[i - 1][0], max(ans[i - 1][1], ans[i - 1][2]));
        // left
        if(pos[i] - h[i] > pos[i-1]){
            ans[i][1] = max(ans[i][1], max(ans[i - 1][0], ans[i - 1][1])) + 1;
        }
        if(pos[i] - h[i] > pos[i-1] + h[i-1]){
            ans[i][1] = max(ans[i][1], ans[i - 1][2] + 1);
        }
        // right
        if(pos[i] + h[i] < pos[i + 1]){
            ans[i][2] = max(ans[i - 1][0], max(ans[i - 1][1], ans[i - 1][2])) + 1;
        }
    }
    int ANS = 0;
    for (int i = 0; i < 3; i++){
        ANS = max(ANS, ans[N - 2][i]);
    }
    cout << ANS + 1 << endl;
    return 0;
}