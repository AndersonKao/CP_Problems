#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define iter vector<int>::iterator
int seq[3005];
int minindex[3005];
int maxindex[3005];
int main(){
    int T;
    cin >> T;
    int N;
    while(T--){
        long long ans = 0;
        memset(minindex, 0, sizeof(minindex));
        memset(maxindex, 0, sizeof(maxindex));
        vector<int> Knum[3005];
        cin >> N;
        for (int i = 1; i <= N; i++){
            cin >> seq[i];
            if(minindex[seq[i]] == 0 || minindex[seq[i]] > i){
                minindex[seq[i]] = i;
            }
            if(maxindex[seq[i]] == 0 || maxindex[seq[i]] < i){
                maxindex[seq[i]] = i;
            }
            Knum[seq[i]].emplace_back(i);
        }
        for (int i = 1; i <= N; i++){
            for (int j = 1 ; j <= N; j++){
                if(i == j)
                    continue;
                if((maxindex[i] == minindex[i]) || (maxindex[j] == minindex[j]) || !maxindex[i] || !maxindex[j])
                    continue;
                if(maxindex[i] > minindex[j] && minindex[i] < minindex[j]){
                    iter itj = upper_bound(Knum[j].begin(), Knum[j].end(), maxindex[i]);
                    iter iti = upper_bound(Knum[i].begin(), Knum[i].end(), minindex[j]);
                    long long jx = 0;
                    long long ix = 0;
                    long long muj, mux;
                    while(itj != Knum[j].end()){
                        itj++;
                        jx++;
                    }
                    while(iti != Knum[i].end()){
                        iti++;
                        ix++;
                    }
                    muj = jx;
                    mux = ix;
                    if(jx == 0)
                        muj = 1;
                    if(ix == 0)
                        mux = 1;
                    ans += (Knum[i].size() - ix) * muj * mux * (Knum[j].size() - jx);
                    continue;
                }
            }
        }
        int todiv = 24;
        for (int i = 1; i <= N; i++){
            if(Knum[i].size() >= 4){
                long long mu = 1;
                
                for (int j = Knum[i].size(); j > Knum[i].size() - 4;j--){
                    mu = mu * j;
                }
                mu /= todiv;
                ans += mu;
            }
        }
        cout << ans << endl;
    }
    return 0;
}