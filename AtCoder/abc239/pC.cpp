#include <bits/stdc++.h>
using namespace std;

int pts[8][2] = {
    {1, 2},
    {2, 1},
    {-1, 2},
    {2, -1},
    {-1, -2},
    {-2, -1},
    {1, -2},
    {-2, 1}};

using PII = pair<long long , long long >;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    PII p1, p2;
    cin >> p1.first >> p1.second >> p2.first >> p2.second;
    set<PII> S;
    for (int i = 0; i < 8; i++){
        S.emplace(p1.first + pts[i][0], p1.second + pts[i][1]);
    }
    bool solve = false;
    for (int i = 0; i < 8; i++){
        PII f(p2.first + pts[i][0], p2.second + pts[i][1]);
        if(S.find(f) != S.end()){
            cout << "Yes\n";
            break;
        }
        if(i == 7){
            cout << "No\n";
        }
    }

    return 0;
}