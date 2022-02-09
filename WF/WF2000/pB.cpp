#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
#define DEBUG3
int T;
char ops[3] = {'+', '-', '*'};
stack<int> S;
stack<int> revS;

bool solve2000;
void recurSum(vector<int>& V, stack<char>& ansChar, int index, long long sum){
    if(index == V.size()){
        if(sum == 2000 && V.size() > 1){
            solve2000 = true;
            stack<char> copyAns(ansChar);
            stack<char> copyAns2;

            while(copyAns.size()){
                copyAns2.emplace(copyAns.top());
           //     cout << copyAns.top();
                copyAns.pop();
            }
            //cout << endl;

            copyAns2.pop();
            cout << "  ";
            for (int i = 0; i < V.size(); i++)
            {
                cout << V[i];
                if(i != V.size() - 1){
                    cout << copyAns2.top();
                    copyAns2.pop();
                } 
            }
            cout << "=\n";
        }
        return;
    }
#ifdef DEBUG2
    cout << "cur sum " << sum << " index = " << index << endl;
#endif
// plus part
    ansChar.emplace('+');
    long long mul = 1;
    for (int i = index; i < V.size(); i++){
        mul *= V[i];
        recurSum(V, ansChar, i + 1, sum + mul);
        ansChar.emplace('*');
    }
    ansChar.pop();
    // pop out *
    for (int i = index; i < V.size(); i++)
        ansChar.pop();
// ----
// minus part
    mul = 1;
    if(index != 0){

    ansChar.emplace('-');
    for (int i = index; i < V.size(); i++){
        mul *= V[i];
        recurSum(V, ansChar, i + 1, sum - mul);
        ansChar.emplace('*');
    }
    ansChar.pop();
    for (int i = index; i < V.size(); i++)
        ansChar.pop();
    }
// ----
#ifdef DEBUG2
    cout << "go back \n";
#endif
}

void parseEvaluate()
{
#ifdef DEBUG
    cout << "what we get in stack ";
#endif
    stack<int> S2(S);
    while(!S2.empty()){
        revS.emplace(S2.top());
        S2.pop();
#ifdef DEBUG
        cout << S.top() << "\n";
#endif
    }
    vector<int> V;
    while(!revS.empty()){
        V.emplace_back(revS.top());
        revS.pop();
    }
    stack<char> ansChar;
#ifdef DEBUG2
    cout << "parsed: ";
    for(auto p: V)
        cout << p << " ";
    cout << endl;
#endif
    recurSum(V, ansChar, 0, 0);
    // put them back
}

void solve(int index, string& str){
    if(str[index] == '='){
        parseEvaluate();
        return;
    }
    bool first = true;
    if(str[index] == '0'){
        S.emplace(0);
        solve(index + 1, str);
        S.pop();
    }else{
        int num = 0;
        for (int i = index; str[i] != '='; i++){
            num += (str[i] - '0');
            S.emplace(num);
            solve(i + 1, str);
            S.pop();
            num *= 10;
        }
    }
}

int main(){
//  cin.tie(0);
    ios_base::sync_with_stdio(false);

    string str;
    int cnt = 0;
    while(cin >> str){
        if(str == "=")
            break;
        cout << "Problem " << ++cnt << endl;
        solve2000 = false;
        while(S.size())
            S.pop();
        while(revS.size())
            revS.pop();
        solve(0, str);
        if(!solve2000)
            cout << "  IMPOSSIBLE\n";
    }

    return 0;
}