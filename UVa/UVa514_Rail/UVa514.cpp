#include <iostream>
#include <stack>
using namespace std;
int N;
int orderSeq[1005];
int main(){
    stack<int> S;
    while(cin >> N){
        if(N == 0){
            break;
        }
        while(true){

            for (int i = 0; i < N; i++){
                cin >> orderSeq[i];
                if(orderSeq[i] == 0){
                    break;
                }
            }
            if(orderSeq[0] == 0){
                cout << "\n";
                break;
            }
            while(!S.empty())
                S.pop();
            int cur = 0;
            int increment = 1;
            S.push(increment);
            increment++;
            bool solve = true;
            while(increment <= N || (!S.empty()))
            {
                if(cur < N && !S.empty() && S.top() == orderSeq[cur])
                {
                    S.pop();
                    cur++;
                }
                else
                    S.push(increment++);
                if(increment == N+1 && !S.empty() && S.top() != orderSeq[cur]){
                    solve = false;
                    break;
                }
            }
            cout << (solve ? "Yes" : "No") << "\n";
        }
    }
    return 0;
}