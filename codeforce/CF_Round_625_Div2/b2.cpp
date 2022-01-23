#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

long long beau[200005];
long long Ans = 0;
int N;
int existance[200005];
vector<long long> storage[400005];
vector<long long> appear;

int binay_search(vector<int>* seq, int target,int L,int R){
    int Mid = (L+R) / 2;
    if()

    return -1;
}

void dp(int index){
    for(int i=index+1;i<=N;i++){
        if(!storage[i].empty()){
            for(int j = 0;j<storage[i].size();j++){
                if(storage[i][j] > i && abs(beau[storage[i][j]] - beau[index])){
                    
                }
            }
        }
    }
}


int main(){
    cin >> N;
    memset(existance,0,sizeof(existance));
    for(int i = 1;i<=N;i++){
        cin >> beau[i];
        storage[beau[i]].push_back(i);
        if(!existance[i]){
            appear.push_back(beau[i]);
            existance[beau[i]] = 1;
        }
    }
    sort(appear.begin(),appear.end());
    if(N == 1)
        cout << beau[1] << "\n";
    else{
        int index;
        bool flag = true;

        }   
    }
    return 0;
}