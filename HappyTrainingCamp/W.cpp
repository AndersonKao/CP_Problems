#include <bits/stdc++.h>
using namespace std;

int T;

void solve(int N){
    int data;
    stack<int> S;
    while(true){
        //cout << "onetime\n";
        while(!S.empty())
            S.pop();
        int next = 1;
        bool solvable = true;
        for (int i = 0; i < N; i++){
            cin >> data;
            if(data == 0)
                return;
            while (S.empty() || S.top() != data)
            {
                if(next > N){
                    solvable = false;
                    break;
                }
                S.push(next);
                next++;
            }
            if(!solvable)
                continue;
            S.pop();
        }
        
        cout << (solvable ? "Yes\n" : "No\n");
    }
}

int main(){
    //cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    bool first = true;
    while(cin >> N){
        if(N == 0)
            break;
        solve(N);
        cout << "\n";
    }

    return 0;
}