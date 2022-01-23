// AC 2020-07-17 15:46:53
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
    std::ios_base::sync_with_stdio(false);
    // cin.tie(0);
    string str;
    while(getline(cin, str)){
        if(str == ".")
            break;
        else if(str == ""){
            cout << "0\n";
            continue;
        }
        vector<int> V = build_kmp(str);
        // int ans = 1;
        // int i;
        
        // for(int i = 0; i < V.size(); i++)
        //     cout << V[i] << ' ';
        // cout << "\n";
        int last_index;
        for(int i = 0; i < V.size(); i++){
            // cout << V[i] << ' ';
            if(V[i] == 0)
                last_index = i;
        }
        string pat = str.substr(0, last_index);
        // cout << pat << '\n';
        vector<int> PAns = kmp_match(V, pat, str);
        if((double)PAns.size() == ((double)str.length() / pat.length()))
            cout << PAns.size() << '\n';
        else
            cout << "1\n";
    }
    return 0;
}
