// AC Feb/26/2021 10:34UTC+8
#include <bits/stdc++.h>
using namespace std;
#define MAX_NUM 200005
// #define DFS1TEST
int seq[MAX_NUM];
vector<int> G[MAX_NUM];
int Ans[MAX_NUM] = {0};
bool visited[MAX_NUM] = {false};
vector<int> factors_of_root;
int div_num[MAX_NUM] = {0};
int gcd(int a, int b){
    if(b==0){
        return a;
    }
        return gcd(b, a%b);
}
void dfs1(int index, int p){ // for root equal 0
    if(p == 0){
        Ans[index] = seq[index];
    }else{
        Ans[index] = gcd(seq[index], Ans[p]);

    }
    for(int w : G[index]){
        if(w != p){
            dfs1(w, index);
        }
    }
}

void dfs2(int index, int d, int p){ // for root not equal 0
    // for(int div: factors[seq[index]]){
    for (int div : factors_of_root){
        if(seq[index] % div == 0)
            div_num[div]++;
        if(div_num[div] >= d){
            Ans[index] = max(Ans[index], div);
        }
    }
    for(int w: G[index]){
        if(w != p){
            dfs2(w, d + 1, index);
        }
    }

    
    for(int div: factors_of_root){
        if(seq[index] % div == 0)
            div_num[div]--;
    }
}


int main(){
    int NUM;
    cin >> NUM;
    for (int i = 0; i < NUM;i++){
        cin >> seq[i];
    }

    for (int i = 1; i * i <= seq[0]; i++){
        if(seq[0] % i == 0){
            factors_of_root.push_back(i);
            if(i * i != seq[0]){
                factors_of_root.push_back(seq[0] / i);
            }
        }
    }
    sort(factors_of_root.begin(), factors_of_root.end());
    int a, b;
    for (int i = 0; i < NUM - 1; i++){
        cin >> a >> b;
        G[a - 1].emplace_back(b - 1);
        G[b - 1].emplace_back(a -1);
    }
    Ans[0] = seq[0];
    dfs1(0, 0);
    #ifdef DFS1TEST
    for (int i = 0; i < NUM; i++)
    {
        cout << Ans[i] << ' ';
    }
    cout << '\n';
    #endif
    dfs2(0, 0, 0);

    for (int i = 0; i < NUM; i++)
    {
        cout << Ans[i] << ' ';
    }
    cout << '\n';
    return 0;
}