#include <bits/stdc++.h>
using namespace std;

#define MAXN 300
bool isprime[MAXN +1];

void buildPrime(){

    fill(isprime, isprime + MAXN, true);
    isprime[0] = false;
    isprime[1] = false;
    for (int i = 2; i <= MAXN; i++){
        if(isprime[i])
            for (int j = i*i; j <= MAXN; j+=i){
                isprime[j] = false;
            }
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    bool yes = false; //
    buildPrime();
        for (int i = A; i <= B; i++)
        {
            for (int j = C; j <= D; j++)
            {
                if (isprime[i + j])
                {
                    break;
                }
                if (j == D)
                    yes = true;
            }
        }
    cout << (yes ? "Takahashi" : "Aoki") << endl;

    return 0;
}