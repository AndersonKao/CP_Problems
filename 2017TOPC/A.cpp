#include <bits/stdc++.h>
using namespace std;
set<int> S1;
set<int> S2, S3;
int main(){
    int T;
    scanf("%d", &T);
    int m, n;
    vector<int> V(100);
    vector<int> V2(100);
    while(T--){
        S1.clear();
        S2.clear();
        V.clear();
        V2.clear();
        int data;
        scanf("%d %d", &m, &n);
        for(int i = 0; i < m; i++)
        {
            scanf("%d", &data);
            S1.emplace(data);
        }
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &data);
            S2.emplace(data);
        }
        vector<int>::iterator it;
        it = set_union(S1.begin(), S1.end(), S2.begin(), S2.end(), V.begin()); 
        V.resize(it - V.begin());
        it = set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), V2.begin()); 
        V2.resize(it - V2.begin());
        if(V.size() < V2.size()*2){
            printf("1\n");
        }
        else
            printf("0\n");
        
        
    }

    return 0;
}