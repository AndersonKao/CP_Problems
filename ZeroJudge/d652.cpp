// AC 2020-02-04 22:53
#include <iostream>
using namespace std;

int seq[55];
int ans[55][55];

int min(int a, int b){
    return  a > b ?  a :  b;
}
int dopose(int indexL,int indexR){

    if(ans[indexL][indexR])
        return ans[indexL][indexR];
    if(indexL+2 == indexR)
        return ans[indexL][indexR] = seq[indexL] * seq[indexL+1] * seq[indexR];
    if(indexL+1 == indexR)
        return ans[indexL][indexR];
        int bans = 100000005;
    for(int i=indexL+1;i<=indexR-1;i++){
      int  to  = dopose(indexL,i) + dopose(i,indexR) + seq[indexL] * seq[i] * seq[indexR];
       bans = bans < to ? bans : to;
    }
    return ans[indexL][indexR] = bans;
}

int main(){
    int N,tmp;
    cin >> N;
    for(int i =0;i< N;i++)
        for(int j=0;j<N;j++)
        ans[i][j] = 0;
    for(int i=0;i<N;i++){
        cin >> seq[i];
    }
    cout << dopose(0,N-1) << "\n";

    return 0;
}