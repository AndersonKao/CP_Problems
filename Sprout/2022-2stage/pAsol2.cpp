#include<bits/stdc++.h>
using namespace std;
map<string, int> typ;
map<string, int> num;
int tonum(string a){
    a.erase(a.begin());
    return num[a];
}
int totyp(string a){
    while(a.size() > 1)a.pop_back();
    return typ[a];
}
bool cmp(string a, string b){
    if(a.size() != 1 && b.size() != 1){
        if(tonum(a) == tonum(b)){
            return totyp(a) < totyp(b);
        }else{
            return tonum(a) < tonum(b);
        }
    }else{
        return a.size() > b.size();
    }
}
int main(){
    typ["C"] = 0;
    typ["D"] = 1;
    typ["H"] = 2;
    typ["S"] = 3;
    num["A"] = 1;
    num["J"] = 11;
    num["Q"] = 12;
    num["K"] = 13;
    for(int i = 2 ; i <= 10 ; i++)num[to_string(i)] = i;
    int t;
    cin >> t;
    vector<string> ve;
    for(int i = 0 ; i < t ; i++){
        string a;
        cin >> a;
        ve.push_back(a);
    }
    sort(ve.begin(), ve.end(), cmp);
    for(int i = 0 ; i < ve.size() ; i++){
        if(i == 0)cout << ve[i];
        else cout << ' ' << ve[i];
    }
    cout << endl;
    return 0;
}