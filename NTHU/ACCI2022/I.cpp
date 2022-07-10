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


int main(){
    int n, q;
    cin >> n >> q;
    vec<vec<int>> recipe(q);
    REP(i, q){
        int size;
        cin >> size;
        REP(j, size){
            int v;
            cin >> v;
            v--;
            recipe[i].eb(v);
        }
    }
    vec<bool> used(n, false);
    vec<bool> reciused(q, false);
    vec<int> buildat(n, -1);
    int ans = 0;
    REP(i, q)
    {
        bool makit = true;
        vec<bool> checked(recipe[i].size(), false);
        vec<int> usding;
        vec<int> usdreci;
        #ifdef Dg
        cout << "doing " << i << endl;
        cout << recipe[i].size() << endl;
        #endif
        for (int j = 0; j < recipe[i].size(); j++)
        {
            if(checked[j]){
            #ifdef Dg
               cout << "checked " << j << endl;
            #endif
                continue;
            }
            int& mtl = recipe[i][j];
            if (used[mtl])
            {
            //    cout << "used " << mtl << endl;
                int bt = buildat[mtl];
                if(reciused[bt]){
             //       cout << "reci " << bt << " is used\n";
                    makit = false;
                    break;
                }
                else{
                    int ptr = 0;
                    vec<int> jst;
                    for (int k = 0; k < recipe[i].size(); k++)
                    {
                        if(ptr == recipe[bt].size())
                            break;
                        if (recipe[i][k] == recipe[bt][ptr]){
                            jst.eb(k);
                            ptr++;
                        }
                    }
                    if(ptr != recipe[bt].size()){
                        makit = false;
              //          cout << "not compatible\n";
                    }
                    else{
                        usdreci.eb(bt);
                        for(int& e:jst){
                            checked[e] = true;
                        }
                    }
                }
            }
            usding.eb(mtl);
        }
        if(makit){
            for (int &ele : usding){
                buildat[ele] = i;
                used[ele] = true;
            }
            for(int &ele:usdreci){
                reciused[ele] = true;
            }
        }
        else{
            ans++;
        }
    }
    cout << ans << endl;

    return 0;
}