#include<iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
bool myfunction (double i,double j) { return (i>j); }
vector<double> VAns;
struct equipment{
    double ad, ap, p;
};
equipment equips[15];
int AnsIndex, N;
vector<int>CurrentUse;
set<vector<int>> AnsSet;
void sol(int Remain, int CIndex){
    
    if(Remain == 0 ){
        if(!AnsSet.count(CurrentUse)){
            equipment data;
            data.ad = data.ap = data.p = 0.0;
            for(int i = 0; i < N; i++){
                data.ad += equips[i].ad * CurrentUse[i];
                data.ap += equips[i].ap * CurrentUse[i];
                data.p += equips[i].p * CurrentUse[i];
            }
            data.p = min(data.p,1.0);
            VAns.push_back((0.2 * data.ap + 0.75 * data.ad) * (1 + data.p));
            AnsSet.insert(CurrentUse);
        }
        return;
    }
    if(Remain < 0 || CIndex < 0)
        return;
    for(int i = 0; i <= Remain; i++){
        CurrentUse[CIndex]+= i;
        sol(Remain-i, CIndex - 1);
        CurrentUse[CIndex]-= i;
    }
}
int main(){
    
    cin >> AnsIndex >> N;
    CurrentUse.resize(N,0);
    for(int i = 0; i < N; i++){
        cin >> equips[i].ap >> equips[i].ad >> equips[i].p;
    }
    sol(6, N-1);
    sort(VAns.begin(), VAns.end(), myfunction);
    // for(auto it: VAns){
    //     cout << it << " ";
    // }
    // cout << endl;
    // for(auto it:AnsSet){
    //     cout << "Used: " ;
    //     for(auto it2: it){
    //         cout << it2 << " ";
    //     }
    //     cout << endl;
    // }
    cout << fixed << setprecision(2) << VAns[AnsIndex-1] << endl;
    return 0;
}