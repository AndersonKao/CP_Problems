#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define F first
#define S second
#define eb emplace_back
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
const int len = 9;

int main(){
    int n;
    cin >> n;
    vec<int> cages(n);
    for(int&e: cages)
        cin >> e;
    vec<vec<int>> cid(10, vec<int>(10));
    vec<vec<int>> table(10, vec<int>(10));

    REP1(i, len){
        REP1(j, len){
            cin >> cid[i][j];
            cid[i][j]--;
        }
    }
    vec<int> csum(n, 0);
    REP1(i, len)
    {
        REP1(j, len){
            int val;
            cin >> val;
            table[i][j] = val;
            csum[cid[i][j]] += val;
        }
    }
    bool sol = true;
    REP1(i, len){
        vec<bool> occur(10, false);
        REP1(j, len){
            if(occur[table[i][j]]){
                sol = false;
            }
            occur[table[i][j]] = true;
        }
    }
    REP1(i, len){
        vec<bool> occur(10, false);
        REP1(j, len){
            if(occur[table[j][i]]){
                sol = false;
            }
            occur[table[j][i]] = true;
        }
    }
    REP(i, 3){
        REP(j, 3){
            int bx = i * 3;
            int by = j * 3;
            vec<bool> occur(10, false);
            REP(x, 3)
            {
                REP(y, 3){
                    if(occur[table[bx+x + 1][by + y + 1]]){
                        sol = false;
                    }
                    occur[table[bx+x + 1][by+y + 1]] = true;
                }
            }
        }
    }
    REP(i, n)
    {
        if(csum[i] != cages[i])
            sol = false;
    }
    cout << (sol ? "YES\n" : "NO\n");
    return 0;
}