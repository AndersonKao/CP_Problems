// AC 2022-02-28 09:57:27
// binary Jumping 
// WA
// 跳的應該要是[__lg(bit)]而不是[bit - 1], 白癡錯誤。
#include <bits/stdc++.h>
using namespace std;

int N, Q;
vector<vector<int>> pa;
void buildLCA(){

}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> Q;
    int Len = __lg(N) + 1;
    pa.resize(N, vector<int>(__lg(N) + 1, -2));
    int u;
    for (int i = 1; i < N; i++){
        cin >> u;
        u--;
        pa[i][0] = u;
    }
    for (int i = 1; i < Len; i++){
        for (int j = 1; j < N; j++){
            pa[j][i] = pa[j][i-1] == -2 ? -2 : pa[pa[j][i - 1]][i - 1];
        }
    }
    /*
    for (int j = 0; j < N; j++){
        cout << j + 1 << ": ";
        for (int i = 0; i < Len;i++){
            cout << pa[j][i] + 1 << " ";
        }
        cout << endl;
    }
    */
        int jump;
    for (int i = 0; i < Q; i++){
        cin >> u >> jump;
        int ans = u - 1;
        while(jump && ans != -2){
            int bit = jump & (-jump);
            jump -= bit;
            //cout << "jump: " << bit << ", " << jump << ", " << ans + 1  << endl;
            ans = pa[ans][__lg(bit)];
        }
        cout << (ans + 1) << endl;
    }
        return 0;
}
/*
10 10
1 2 3 4 5 6 7 8 9
6 1
7 4
6 2
10 4
9 7
8 5
1 1
9 8
4 1
4 3
*/