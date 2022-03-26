// AC 2022-02-11 04:32:59
#include <bits/stdc++.h>
#define debug
using namespace std;
using PII = pair<int, int>;
// dp[i][j] = max{dp[i-1][k], for all k s.t. 1 <= k < j};
// i的階層可以省略，維護k的方式用BIT，logN 修改/得到 前k個的最大值
// BIT 維護以 <= i 值為結尾的LIS長度
vector<int> seq;
void update(vector<int> &BIT, int n, int data);
int query(vector<int> &BIT, int n);
void coord(vector<int>& V){
    vector<int> arr(V);
    sort(arr.begin(), arr.end());
#ifdef debugcoord
    for(auto c: arr){
        cout << c << " ";
    }
    cout << endl;
#endif
    map<int, int> index;
    int cur = 1;
    for (int i = 0; i < arr.size(); i++){
        map<int, int>::iterator iter = index.find(arr[i]);
        if(iter == index.end())
            index[arr[i]] = cur++;
    }
    for (int i = 0; i < V.size(); i++){
        V[i] = index[V[i]];
    }
#ifdef debugcoord
    for(auto c: V){
        cout << c << " ";
    }
    cout << endl;
#endif

}
void solve(int N){
    vector<int> BIT;
    BIT.resize(N + 1, 0);
    int curlen;
    for (int i = 0; i < N; i++){
        curlen = query(BIT, seq[i]-1);
        curlen++;
        update(BIT, seq[i], curlen);
    }
    cout << query(BIT, N) << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    seq.resize(N);
    for (int i = 0; i < N; i++){
        cin >> seq[i];
    }
    coord(seq);
    solve(N);

    return 0;
}
void update(vector<int> &BIT, int index, int data){
    while(index < BIT.size()){
        BIT[index] = max(BIT[index], data);
        index += (index) & (-index);
    }
}
int query(vector<int> &BIT, int index){
    int ans = 0;
    while(index>0){
        ans = max(BIT[index], ans);
        index -= (index) & (-index);
    }
    return ans;
}