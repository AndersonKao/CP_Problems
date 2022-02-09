#include <bits/stdc++.h>
using namespace std;

vector<int> seq[1000000];
void solve(int N, int M)
{
//    cin >> N >> M;
    for (int i = 0; i < 1000000; i++)
        seq[i].clear();
    int data;
    for (int i = 0; i < N; i++)
    {
        cin >> data;
        seq[data - 1].emplace_back(i);
    }
    int k, v;
    while(M--){
        cin >> k >> v;
        v -= 1;
        if(seq[v].empty()){
            cout << "0\n";
        }else{
            if(k > seq[v].size()){
                cout << "0\n";
            }else{
                cout << seq[v][k - 1] + 1 << endl;
            }
        }
    }
}

int main(){
    //cin.tie(0);
    //ios_base::sync_with_stdio(false);
    int N, M;
    while(cin >> N >> M){
        solve(N, M);
    }

    return 0;
}