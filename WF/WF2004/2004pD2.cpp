#include <bits/stdc++.h>
#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
template <typename T>
using vec = vector<T>;
struct Fenwick{
    int range;
    vec<int> V;
    Fenwick(int n){
        range = n;
        V.resize(range + 1, 0);
    }
    Fenwick(const Fenwick& cpy){
        V = cpy.V;
        range = cpy.range;
    }
    void add(int idx, int val){
        int res = idx;
        while(res <= range){
            V[res] += val;
            res += (res & (-res));
        }
    }
    int psum(int idx){
        int ans = 0;
        while (idx > 0)
        {
            ans += V[idx];
            idx -= (idx & (-idx));
        }
        return ans;
    }
    int val(int idx){
        return psum(idx) - psum(idx - 1);
    }
    void reset(){
        fill(V.begin(), V.end(), 0);
        REP1(i, range)
        {
            this->add(i, 1);
        }
    }
};
vec<int> chnt;
bool getPrague(Fenwick & Fen, const string& str, int s, int i, int n, string& res){
    //cout << "gettingPrague of " << str << "   -------------\n";
    //cout << "chossing s = " << s + 1 << " i = " << i + 1 << " n = " << n << endl;
    res = ("");
    vec<int> taken(26, 0);
    int cur = s + 1;
    int finding = Fen.psum(cur);
    int size = Fen.psum(str.length());
    //cout << "now having " << size << endl;
    for (int cnt = 0; cnt < n; cnt++)
    {
        if(cnt != 0)
            finding = cur + i;
        if(finding > size)
            finding = (finding - 1) % size + 1;
        int l = 1, r = str.length();
        //cout << "finding : " << finding;
        while (l < r)
        {
            int m = (l + r) >> 1;
            int val = Fen.psum(m);
            if(val < finding){
                l = m + 1;
            }else{
                r = m;
            }
        }
        //cout << ", found l: " << l << endl;
        int ch = str[l - 1] - 'A';
        taken[ch]++;
        if(taken[ch] > (chnt[ch] >> 1))
            return false;
        res += str[l - 1];
        Fen.add(l, -1);
        size--;
        cur = finding;
    }
    //cout << "res: " << res << endl;
    return true;
}
bool getPrague2(Fenwick & Fen, const string& str, int s, int i, int n, string&res, const string& p){
    //cout << "gettingPrague of " << str << "   -------------\n";
    //cout << "chossing s = " << s + 1 << " i = " << i + 1 << " n = " << n << endl;
    res = "";
    int cur = s + 1;
    int finding = Fen.psum(cur);
    int size = Fen.psum(str.length());
    //cout << "now having " << size << endl;
    for (int cnt = 0; cnt < n; cnt++)
    {
        if(cnt != 0)
            finding = cur + i;
        if(finding > size)
            finding = (finding - 1) % size + 1;
        int l = 1, r = str.length();
        //cout << "finding : " << finding;
        while (l < r)
        {
            int m = (l + r) >> 1;
            int val = Fen.psum(m);
            if(val < finding){
                l = m + 1;
            }else{
                r = m;
            }
        }
        //cout << ", found l: " << l << endl;
        if(str[l - 1] != p[cnt])
            return false;
        res += str[l - 1];
        Fen.add(l, -1);
        size--;
        cur = finding;
    }
    //cout << "res: " << res << endl;
    return true;
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
        Fenwick F(m);

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
                    // Fenwick here
                 
                    F.reset();

                    if(!getPrague(F, str, s, i, n, p))
                        continue;
                         //       cout << p << " with " << s << ", " << i << endl;

                    for (int t = 0; t < m; t++){
                        if(str[t] != p[0] || F.val(t + 1) == 0 /*position p is empty and */ )
                            continue;
                        for (int j = i + 1; j < m; j++){
                            // Fenwick2 here, copied Fenwick
//                            cout << "heloo\n";
                            Fenwick F2(F);
                            if(getPrague2(F2, str, t, j, n, c, p)){
                                //cout << c << " with " << t << ", " << j << endl;

                                if (p == c)
                                {
                                    if(sol == 0){
                                        ans = c;
                                        
            //                            cout << c << endl;
                                        sol++;
                                    }
                                    else{
                                        if(p != ans){
                                            sol++;
                                        //    cout << "possi: " << p << endl;
                                        }
                                    }
                                }
                            }    if(sol >= 2)
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