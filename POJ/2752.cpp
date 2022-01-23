// AC 2020-07-16 15:50:14
#include <iostream>
#include <vector>
#include <stack>
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
int main(){
    string str;
    
    while(cin >> str){
        vector<int> V = build_kmp(str);
        // for(auto it: V)
        //     cout << it << ' ';
        // cout << '\n';
        stack<int>Ans;
        int tmp = V[V.size() - 1];
        while(~tmp){
            Ans.push(tmp + 1);
            tmp = V[tmp];
        }
        // Ans.push_back(str.length());
        while(!Ans.empty()){
            cout << Ans.top() << ' ';
            Ans.pop();
        }
        cout << str.length() << '\n';
    }


    return 0;
}