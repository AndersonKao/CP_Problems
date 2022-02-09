#include <bits/stdc++.h>
using namespace std;

int seq[200000];
using Iter = multiset<int>::iterator;
using rIter = multiset<int>::reverse_iterator;

void printSets(multiset<int> &a, multiset<int> &b){
    return;
    cout << "SM: ";
    for(auto p: a)
        cout << p << " ";
    cout << endl;
    cout << "SL: ";
    for(auto p: b) 
        cout << p << " ";
    cout << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, k;
    cin >> N >> k;
    for (int i = 0; i < N; i++)
        cin >> seq[i];
    vector<int> V(seq, seq + k);
    sort(V.begin(), V.end());
    int cur_median = V[(V.size() - 1) / 2];

    multiset<int> SM, SL;

    for (int i = 0; i < k; i++){
        if(seq[i] <= cur_median)
            SM.emplace(seq[i]);
        else
            SL.emplace(seq[i]);
    }
    cout << cur_median ;

    printSets(SM, SL);

    int data, toRemove;
    for (int i = k; i < N; i++){

        data = seq[i];
        toRemove = seq[i - k];
        if(data <= cur_median){
            SM.emplace(data);
        }
        else{
            SL.emplace(data);
        }
        Iter gotchu;
        if(toRemove <= cur_median){
            gotchu = SM.find(toRemove);
            SM.erase(gotchu);
        }else{
            gotchu = SL.find(toRemove);
            SL.erase(gotchu);
        }
       // cout << "before the fall\n";
        while(SM.size() > SL.size() && SM.size() - SL.size()> 1){
      //      cout << "SM need adjust\n";
            printSets(SM, SL);
            gotchu = SM.end();
            gotchu--;
            SL.emplace(*gotchu);
            SM.erase(gotchu);
        }
        while(SL.size() > SM.size() && SL.size() - SM.size() > 0){
     //       cout << "SL need adjust\n";
            printSets(SM, SL);
            gotchu = SL.begin();
            SM.emplace(*gotchu);
            SL.erase(gotchu);
        }
        cur_median = *SM.rbegin();

     //   cout << "ata\n";
        printSets(SM, SL);
        cout << " " << cur_median;
    }
    cout << endl;

    return 0;
}