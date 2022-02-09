#include <bits/stdc++.h>
using namespace std;

int T;

int target[1000];
int targetcnt[10];
int copycnt[10];
int guess[1000];
int guesscnt[10];
void solve(int N){
    fill(targetcnt, targetcnt + 10, 0);
    for (int i = 0; i < N; i++){
        cin >> target[i];
        targetcnt[target[i]]++;
    }
    bool end = true;
    for (int i = 0; i < N; i++){
        cin >> guess[i];
        if(guess[i] != 0)
            end = false;
    }
    int strong, weak;
    while(!end){
        strong = weak = 0;
        fill(guesscnt, guesscnt+ 10, 0);
        for (int i = 0; i < 10; i++)
            copycnt[i] = targetcnt[i];
        for (int i = 0; i < N; i++)
            guesscnt[guess[i]]++;
            // strong
        for (int i = 0; i < N; i++)
        {
            if (target[i] == guess[i])
            {
                strong++;
                guesscnt[guess[i]]--;
                copycnt[target[i]]--;
            }
        }
        // weak
        for (int i = 0; i < 10; i++){
            weak += min(guesscnt[i], copycnt[i]);
        }
        cout << "    (" << strong << "," << weak << ")\n";
        end = true;
        for (int i = 0; i < N; i++){
            cin >> guess[i];
            if(guess[i] != 0)
                end = false;
        }
    }
}

int main(){
    // cin.tie(0);
    //ios_base::sync_with_stdio(false);
    int N;
    T = 1;
    while (cin >> N)
    {
        if(N == 0)
            break;
        cout << "Game " << T << ":\n";
        T++;
        solve(N);
    }

    return 0;
}