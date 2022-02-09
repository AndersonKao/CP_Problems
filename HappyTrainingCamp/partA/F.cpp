#include <bits/stdc++.h>
using namespace std;

#define L 1000001
int T;
bool isprime[L] = {true};
void primeTable(){
    fill(isprime, isprime + L, true);
    isprime[1] = false;
    vector<int> prime;
    for (int i = 2; i <= L; i++)
    {
        if(isprime[i])
            prime.push_back(i);
        for (int j = 0; i * prime[j] <= L; j++)
        {
            isprime[i * prime[j]] = false;
            if(i % prime[j] == 0)
                break;
        }
    }
}

vector<pair<int,int>> seq[200005];

long long countit(vector<pair<int, int>> &V)
{

    unsigned len = V.size();
    long long ans = 0;
    bool prevOne, nextOne = false;
    for (int i = 0; i < len; i++)
    {
        prevOne = nextOne = false;
        if(isprime[V[i].first])
        {
            if(i-1 >= 0 && V[i-1].first == 1){
                prevOne = true;
                ans += V[i - 1].second;
            }
            if(i + 1 < len && V[i+1].first == 1){
                nextOne = true;
                ans += V[i + 1].second;
            }
            if(prevOne && nextOne)
                ans += (long long)V[i - 1].second * V[i + 1].second;
            
        }
    }
    return ans;
}

void solve(){
    int n, e;
    cin >> n >> e;
    int data;
    int eindex = 0;
    for (int i = 0; i < e; i++)
        seq[i].clear();
    for (int i = 0; i < n; i++)
    {
        cin >> data;
        if(data == 1 && !seq[eindex].empty() && (seq[eindex].back().first) == 1)
            seq[eindex].back().second++;
        else
            seq[eindex].emplace_back(data, 1);
        eindex = (eindex == e - 1 ? 0 : eindex + 1);
    }
    // debug
    /*
    cout << "---------------\n";
    for (int i = 0; i < e; i++)
    {
        cout << "ein = " << i << endl;
        for(auto p: seq[i])
        {
            cout << "(" << p.first << ", " << p.second << ")\n";
        }
    }
    */
    long long ans = 0;
    for (eindex = 0; eindex < e; eindex++)
    {
        ans += countit(seq[eindex]);
    }
    cout << ans << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> T;
    primeTable();
    while(T--){
        solve();
    }

    return 0;
}