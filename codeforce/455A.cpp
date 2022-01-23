// AC Jul/08/2020 16:36UTC+8
#include <iostream>
#include <algorithm>

using namespace std;

long long intNum[100005] = {0};
long long ansseq[100005] = {0};
int main(){
    int N, data, MAX = INT32_MIN;
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> data;
        intNum[data]++;
        MAX = max(MAX, data);
    }
    ansseq[0] = 0;
    ansseq[1] = intNum[1];
    for(int i = 2; i <= MAX; i++){
        ansseq[i] = max(ansseq[i-1], ansseq[i-2] + intNum[i] * i);
    }
    cout << ansseq[MAX] << '\n';
    return 0;
}