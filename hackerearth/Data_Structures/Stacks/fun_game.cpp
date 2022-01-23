#include<bits/stdc++.h>
using namespace std;

int seq[1000006];
vector<int> ans;
int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> seq[i];
    }
    stack<int> A;
    stack<int> B;
    for (int i = 0; i < n; i++){
        B.push(seq[i]);
    }
    for (int i = n-1; i >= 0; i--){
        A.push(seq[i]);
    }
    while(A.size() && B.size()){
        int x, y;
        x = A.top();
        y = B.top();
        if(x > y){
            ans.push_back(1);
            B.pop();
        }else if(x < y){
            ans.push_back(2);
            A.pop();
        }
        else{
            ans.push_back(0);
            A.pop();
            B.pop();
        }
    }
    for (int i = 0; i < ans.size(); i++){
        cout << ans[i] << (i == ans.size() - 1 ? '\n' : ' ');
    }
}