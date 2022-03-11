#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){

}

int Bnum[5001];
int Anum[5001];
int A[5000];
int B[5000];
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    int d;
    bool gone[5000];
    fill(Anum, Anum + 5001, 0);
    fill(Bnum, Bnum + 5001, 0);
    fill(gone, gone + N, true);
    for (int i = 0; i < N; i++){
        cin >> A[i];
        Anum[A[i]]++;
    }

    for (int i = 0; i < N; i++){
        cin >> B[i];
        Bnum[B[i]]++;
    }
    for (int i = 1; i <= 5000; i++){
        if(Anum[i] != Bnum[i]){
            cout << "No\n";
            return 0;
        }
    }
    for (int i = 0; i < N - 3; i++){
        for (int j = 0; j < N; j++){
            if(B[i] == A[j]){
                gone[j] = false;
            }
        }
    }
    int r[3];
    int rj = 0;
    for (int i = 0; i < N; i++){
        if(gone[i]){
            r[rj++] = A[i];
        }
    }
    int x, y, z;
    x = B[N - 3];
    y = B[N - 2];
    z = B[N - 1];
    if((r[0] == x && r[1] == y && r[2] == z) || (r[0] == y && r[1] == z && r[2] == x) || r[0] == z && r[1] == x && r[2] == y)
        cout << "Yes\n";
    else
        cout << "No\n";

    return 0;
}