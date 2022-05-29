#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define al(x) x.begin(), x.end()
template <typename T>
using vec = vector<T>;
using orderset = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
vec<int> chnt;
vec<bool> postaken;
bool getPrague(orderset &Oset, const string &str, int s, int i, int n, string &res)
{
    //cout << "gettingPrague of " << str << "   -------------\n";
    //cout << "chossing s = " << s + 1 << " i = " << i + 1 << " n = " << n << endl;
    res = ("");
    vec<int> taken(26, 0);
    int cur = s + 1;
//    int finding = Fen.psum(cur);
    int finding = Oset.order_of_key(cur) + 1;
//    int size = Fen.psum(str.length());
    int size = Oset.size();
    // cout << "now having " << size << endl;
    for (int cnt = 0; cnt < n; cnt++)
    {
        if(cnt != 0)
            finding = cur + i;
        if(finding > size)
            finding = (finding - 1) % size + 1;
        auto it = Oset.find_by_order(finding - 1);
//        cout << "finding < " << finding << endl;
        int l = *it;
 //       cout << ", found l: " << l << endl;
        int ch = str[l - 1] - 'A';
        taken[ch]++;
        if(taken[ch] > (chnt[ch] >> 1))
            return false;
        res += str[l - 1];
        postaken[l] = true;
        //        Fen.add(l, -1);
        Oset.erase(it);
        size--;
        cur = finding;
    }
    //cout << "res: " << res << endl;
    return true;
}
bool getPrague2(orderset& Oset, const string& str, int s, int i, int n, string&res, const string& p){
    //cout << "gettingPrague of " << str << "   -------------\n";
    //cout << "chossing s = " << s + 1 << " i = " << i + 1 << " n = " << n << endl;
    res = "";
    int cur = s + 1;
    //int finding = Fen.psum(cur);
    int finding = Oset.order_of_key(cur) + 1;
//    int size = Fen.psum(str.length());
    int size = Oset.size();
    //cout << "now having " << size << endl;
    for (int cnt = 0; cnt < n; cnt++)
    {
        if(cnt != 0)
            finding = cur + i;
        if(finding > size)
            finding = (finding - 1) % size + 1;
        auto it = Oset.find_by_order(finding - 1);
        int l = *it;
        // cout << ", found l: " << l << endl;
        if(str[l - 1] != p[cnt])
            return false;
        res += str[l - 1];
//        Fen.add(l, -1);
        Oset.erase(it);
        size--;
        cur = finding;
    }
    //cout << "res: " << res << endl;
    return true;
}

void ReSet(orderset& O, int m){
    O.clear();
    for (int i = 1; i <= m; i++)
        O.insert(i);
}
int main()
{
    yccc;
    int round = 1;
    string str;
    while (cin >> str)
    {
        if(str == "X")
            break;
        string ans;
        chnt.clear();
        chnt.resize(26, 0);
        int m = str.length();
        REP(i, m){
            chnt[(str[i] - 'A')]++;
        }
//        Fenwick F(m);

        orderset O;
        postaken.resize(m + 1);

        long long sol = 0;
        string p, c;
 //       cout << str.length() << endl;
        
        for (int n = (m >> 1); n >= 1; n--)
        {
//            cout << "try n = " << n << endl;
            for (int s = 0; s < m; s++)
            {
                if(chnt[(str[s] - 'A')] == 1)
                    continue;
                for (int i = 0; i < m - 1; i++){
                    ReSet(O, m);
                    fill(al(postaken), false);

                    if(!getPrague(O, str, s, i, n, p))
                        continue;

                    for (int t = 0; t < m; t++){
                        if(str[t] != p[0] || postaken[t + 1]/*position p is empty and */ )
                            continue;
                        for (int j = i + 1; j < m; j++){
                            orderset O2(O);
                            if (getPrague2(O2, str, t, j, n, c, p))
                            {

                                if (p == c)
                                {
                                    if(sol == 0){
                                        ans = c;
                                        sol++;
                                    }
                                    else{
                                        if(p != ans){
                                            sol++;
                                        }
                                    }
                                }
                            }
                            if(sol >= 2)
                                break;
                        }
                        if(sol >= 2)
                            break;
                    }
                    if(sol >= 2)
                        break;
                }
                if(sol >= 2)
                    break;
            }
            if (sol)
                break;
        }
        cout << "Code " << round++ << ": ";
        if (sol == 1)
        {
            cout << ans << endl;
        }
        else if (sol > 1)
        {
            cout << "Codeword not unique" << endl;
        }
    }

    return 0;
}