#include <bits/stdc++.h>
using namespace std;

int T;

using Iter = multiset<int>::iterator;
int seq[200000];
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> seq[i];
    vector<int> V;
    for (int i = 0; i < k; i++)
        V.emplace_back(seq[i]);
    sort(V.begin(), V.end());

    multiset<int> SM, SL;
    int cur_median = V[(V.size() -1)/ 2];

    for (int i = 0; i < k; i++){
        if(seq[i] <= cur_median){
            SM.emplace(seq[i]);
        }else{
            SL.emplace(seq[i]);
        }
    }
    cout << cur_median;

    int toremove, toAdd;
    Iter tode;
    for (int i = k; i < n; i++){
        toremove = seq[i - k];
        toAdd = seq[i];

        if(toAdd <= cur_median){
            SM.emplace(toAdd);
        }else{
            SL.emplace(toAdd);
        }
        if(toremove <= cur_median){
       //        SM.erase(toremove);
            tode = SM.find(toremove);
            SM.erase(tode);
        }else{
//            SL.erase(toremove);
            tode = SL.find(toremove);
            SL.erase(tode);
        }

        Iter elem;
        while(SM.size() > SL.size() && SM.size() - SL.size() > 1){
            elem = SM.end();
            elem--;
            SL.emplace(*elem);
            SM.erase(elem);
        }
        while(SL.size() > SM.size() && SL.size() - SM.size() > 0){
            elem = SL.begin();
            SM.emplace(*elem);
            SL.erase(elem);
        }
        cur_median = *(SM.rbegin());

        cout << " " << cur_median;
    }
    cout << endl;

    return 0;
}