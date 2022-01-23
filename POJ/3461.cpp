// AC 2020-07-16 14:58:48
#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector <int> build_kmp(const string &P) {
    vector <int> f(P.size());
    int fp = f[0] = -1;
    for (int i = 1; i < P.size(); ++i) {
        while (~fp && P[fp + 1] != P[i])
            fp = f[fp];
        if (P[fp + 1] == P[i])
            ++fp;
        f[i] = fp;
        // for testing
        // cout << "Now i= " << i << '\n';
        // for(int i=0;i < P.size(); i++)
        //     cout << P[i] << ' ';
        // cout << '\n';
        // for(auto it = f.begin(); it != f.end(); ++it)
        //     cout << *it <<' ';
        // cout << '\n';
        // cout << "fp equal to " << fp << '\n';
    }
    
    return f;
}
vector <int> kmp_match(vector <int> fail, const string &P, const string &T)
{
    vector <int> res; // start from these points
    const int n = P.size();
    for (int j = 0, i = -1; j < T.size(); ++j) {
        while (~i && T[j] != P[i + 1]) 
            i = fail[i];
        if (P[i + 1] == T[j])
            ++i;
        if (i == n - 1) 
            res.push_back(j - n + 1), i = fail[i];
    }
    return res;
}

int main(){
    string t_pattern;
    string t_text;
    int T;
    cin >> T;
    while(T--){
        cin >> t_pattern >> t_text;
        vector<int>f = build_kmp(t_pattern);
        vector<int>Ans = kmp_match(f, t_pattern,t_text);
        cout << Ans.size() << '\n';
    }

    return 0;
}