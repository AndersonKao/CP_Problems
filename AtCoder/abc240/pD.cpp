#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){

}

using PII = pair<int, int>;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    stack<PII> S;

    int N;
    cin >> N;
    int realnum = 0;
    for (int i = 0; i < N; i++){
        int data;
        cin >> data;

        if(S.empty() || S.top().first != data){
            S.emplace(data, 1);
            realnum++;
        }
        else if(S.top().first == data){
            S.top().second++;
            realnum++;
            if(S.top().second == data){
                realnum -= S.top().second;
                S.pop();

            }
        }
        cout << realnum<< endl;
    }

        return 0;
}