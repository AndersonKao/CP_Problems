#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin >> N;
    set<int> S;
    for (int i = 0; i < N;i++){
        int data;
        cin >> data;
        S.emplace(data);
    }
    cout << S.size() << endl;

    return 0;
}