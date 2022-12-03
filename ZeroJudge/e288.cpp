// AC 2020-07-13 16:36
#include <iostream>
#include <string>
#include <cmath>
#include <map>
using namespace std;
long long Dict[2000];
long long currentdata;
int CaseNum, N;
map<long long, int> MP;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    long long tmp = 1;
    long long ans = 0;
    for(char ch = 'A'; ch <= 'Z'; ch++){
        Dict[ch] = tmp;
        tmp = (tmp<<1);
        // cout << Dict[ch] << '\n'; 
    }
    for(char ch = 'a'; ch <= 'l'; ch++){
        Dict[ch] = tmp;
        tmp = (tmp<<1);
        // cout << Dict[ch] << '\n';
    }
    cin >> CaseNum >> N;
    // cout << "CaseNum: " << CaseNum << '\n';
    string str;
    int limit;
    long long caseLimit = pow(2, CaseNum) - 1;
    for(int i = 0; i < N; i++){
        cin >> str;
        currentdata = 0;
        limit = str.length();
        for(int j = 0; j < limit; j++){
            currentdata |= Dict[str[j]];
        }
        map<long long, int>::iterator it = MP.find(currentdata);
        map<long long, int>::iterator it2 = MP.find(caseLimit - currentdata);
        if(it2 != MP.end())
            ans += it2->second;
        if(it == MP.end()){
            MP[currentdata] = 1;
        }else
            (it->second)++;
    }

    cout << ans << '\n';
    
    return 0;
}

