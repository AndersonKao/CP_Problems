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
int counter;
int strncmp_match(const char *s, const char *t, int n)
{
    int match = 0;
    for (int i = 0; i < n; i++) {
        counter++;
        if (s[i] != t[i])
            break;
        match++;
    }
    return match;
}

int main(){

    int N;
    cin >> N;
    vec<string> strs(N);
    for(string&e: strs)
        cin >> e;
    int n = min(strs[0].length(), strs[1].length());
    int theone = 0;
    int lastn = n;
    for (int i = 1; i < N; i++)
    {
        n = strncmp_match(strs[i - 1].c_str(), strs[i].c_str(), n);
        if(n < lastn){
            theone = i;
        }
        if(n == lastn){
            if(strs[i].length() < strs[theone].length())
                theone = i;
        }
        lastn = n;
    }
    swap(strs[0], strs[theone]);
    counter = 0;
    n = min(strs[0].length(), strs[1].length());
    for (int i = 1; i < N; i++){
        n = strncmp_match(strs[i - 1].c_str(), strs[i].c_str(), n);
    }
    cout << counter << endl;
    return 0;
}