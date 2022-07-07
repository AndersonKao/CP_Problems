#include <bits/stdc++.h>
using namespace std;

int main(){
    int L, N;
    cin >> L >> N;
    vector<int> V(N);
    for (int i = 0; i < N; i++)
        cin >> V[i];
    sort(V.begin(), V.end());
    int MinA = 0;
    for (int i = 0; i < N; i++){
        if(V[i] >= L/2)
            MinA = max(MinA, L - V[i]);
        else
            MinA = max(MinA, V[i]);
    }
    int MaxA = 0;
    MaxA = max(MaxA, V.back());
    MaxA = max(MaxA, L - V[0]);
    cout << MinA << " " << MaxA << endl;

    return 0;
}