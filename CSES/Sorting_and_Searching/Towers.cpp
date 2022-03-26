// AC 2022-02-10 11:01:35
#include <bits/stdc++.h>
using namespace std;

using Iter = multiset<int>::iterator;
multiset<int> S;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    int data;
    for (int i = 0; i < N; i++){
        cin >> data;
        Iter it = S.upper_bound(data);
        if(it == S.end()){
            S.emplace_hint(it, data);
        }else{
            Iter toremove = it;
            it++;
            S.erase(toremove);
            S.insert(it, data);
        }
    }
    cout << S.size() << endl;

    return 0;
}