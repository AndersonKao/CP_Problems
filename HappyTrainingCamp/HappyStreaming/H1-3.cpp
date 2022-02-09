#include <bits/stdc++.h>
using namespace std;

int T;

#define MAXN 1000001
bool prime[MAXN];
 
void eratosthenes()
{
 //   for (int i=0; i<MAXN; i++)
  //      prime[i] = true;
//    memset(prime, true, sizeof(prime));
    fill(prime, prime + MAXN, true);

    prime[0] = false;
    prime[1] = false;
 
    for (long long i=2; i<MAXN; i++)
        if (prime[i])
            for (long long j=i*i; j<MAXN; j+=i)
                prime[j] = false;
}
vector<pair<int, int>> seq[200000];

long long countit(vector<pair<int, int>> & seq){
    long long ans = 0;
    for (int i = 0; i < seq.size(); i++){
        if(prime[seq[i].first]){
            bool frontOne, nextOne;
            frontOne = nextOne = false;

            if(i - 1 >= 0 && seq[i-1].first == 1){
                frontOne = true;
                ans += seq[i - 1].second;
            }
            if(i + 1 < seq.size() && seq[i+1].first == 1){
                nextOne = true;
                ans += seq[i + 1].second;
            }
            if(frontOne && nextOne){
                ans += (long long)seq[i - 1].second * seq[i + 1].second;
            }

        }
    }
    return ans;
}

void solve(){
    int n, e;
    cin >> n >> e;
    int data;
    for (int i = 0; i < n; i++)
        seq[i].clear();
    int cnt = 0;
    for (int i = 0; i < n; i++){
        cin >> data;
        if(data == 1 && !seq[cnt].empty() && seq[cnt].back().first == 1){
            seq[cnt].back().second++;
        }else{
            seq[cnt].emplace_back(data, 1);
        }
        cnt++;
        if(cnt == e){
            cnt = 0;
        }
    }
    long long ans = 0;
    for (int i = 0; i < e; i++){

        ans += countit(seq[i]);
    }
    cout << ans << endl;
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    eratosthenes();
    cin >> T;
    while(T--){
        solve();
    }

    return 0;
}