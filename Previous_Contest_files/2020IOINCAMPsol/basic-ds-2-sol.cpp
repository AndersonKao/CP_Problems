#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int N;
priority_queue<int> PL;
priority_queue<int, vector<int>, greater<int>> PR;
vector<int> ans[2];
int seq[200005];
int main(){
    cin >> N;
    for(int i = 0; i < 3*N; i++){
        cin >> seq[i];
    }
    int ANS = 0;
    for(int i = 0; i < 3*N; i++){
        PR.push(seq[i]);
        if(PL.size()+PR.size() >= 3){
            while(PR.top() < PL.top()){
                
            }
        }
        if((i + 1) % 3 == 0){
            ans[0].push_back(ANS);
        }
    }
    return 0;
}