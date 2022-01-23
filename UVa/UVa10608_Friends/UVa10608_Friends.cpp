// AC 2019-10-21 13:55:21
#include <stdio.h>
#include <iostream>
using namespace std;
int s[30001];
int sum[30001];
void init(int x){
    for(int i =0;i<=x;i++){
        s[i] = i;
        sum[i] = 1;
    }
}
int findM(int x)
{
    if(s[x] == x)
        return x;
    return s[x] = findM(s[x]);
}

void Unite(int x,int y){
    if(sum[findM(x)] >= sum[findM(y)]){
        sum[findM(x)] += sum[findM(y)];
        s[findM(y)] = findM(x);
    }else{
        sum[findM(y)] += sum[findM(x)];
        s[findM(x)] = findM(y);
    }
   
}
bool sam(int x,int y){
    return findM(x) == findM(y);
}

int main()
{
    int T,N,M,x,y,max;
    cin >> T;
    while(T--){
        cin >> N >> M;
        init(N);
        while(M--){
            cin >> x >> y;
            if(!sam(x,y))
            {
                Unite(x, y);
                //cout << "connecting" << x << '&' << y << '\n';
            }
                
        }
        max = 0;
        for (int i = 1; i <= N;i++){
            if(max < sum[i])
                max = sum[i];
          // cout << sum[i] << ' ';
        }
        cout << max << '\n';
    }
    return 0;
}
/*

10 12
1 2
3 1
3 4
5 4
3 5
4 6
5 2
2 1
7 1
1 2
9 10
8 9
*/