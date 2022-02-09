#include <bits/stdc++.h>
using namespace std;

int T;

int seq[1000];
int seqcnt[10];
int copycnt[10];
int guess[1000];
int guesscnt[10];

void solve(int N){
    fill(seqcnt, seqcnt + 10, 0);
    for (int i = 0; i < N; i++){
        cin >> seq[i];
        seqcnt[seq[i]]++;
    }

    fill(guesscnt, guesscnt+ 10, 0);
    for (int i = 0; i < N; i++){
        cin >> guess[i];
        guesscnt[guess[i]]++;
    }
    bool end = false;
    int strong, weak;
    while(!end){
        strong = weak = 0;
        for (int i = 1; i < 10; i++)
            copycnt[i] = seqcnt[i];
        for (int i = 0; i < N; i++)
        {
            if (guess[i] == seq[i])
            {
                strong++;
                guesscnt[guess[i]]--;
                copycnt[guess[i]]--;
            }
        }
        for (int i = 1; i < 10; i++){
            weak += min(guesscnt[i], copycnt[i]);
        }
        cout << "    (" << strong << "," << weak << ")\n";
        fill(guesscnt, guesscnt+ 10, 0);
        bool allzero = true;
        for (int i = 0; i < N; i++){
            cin >> guess[i];
            if(guess[i] != 0)
                allzero = false;
            guesscnt[guess[i]]++;
        }
        if(allzero)
            end = true;
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    int cnt = 1;
    while(cin >> N){
        if(N == 0)
            break;
        cout << "Game " << cnt << ":\n";
        cnt++;
        solve(N);
    }

    return 0;
}