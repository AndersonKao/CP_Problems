#include<bits/stdc++.h>
using namespace std;
#define int long long int
int32_t main(){
    int n, s[100005] = {}, na = 0;
    cin >> n;
    for(int i = 0 ; i < n ; i++){
        cin >> s[i];
        na += s[i];
    }
    if(n >= 3 ){
        if(na >3)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
        return 0;
    }else if(n == 1){
        int fi = 0;
        for(int i = 2 ; i*i <= s[0] ; i++){
            if(s[0] % i == 0){
                fi = 1;
                break;
            }
        }
        if(fi){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }else{
        int all = s[0] + s[1], fi = 0;
        for(int i = 2 ; i*i <= all ; i++){
            if(all % i == 0){
                fi = 1;
                break;
            }
        }
        for(int i = 2 ; i*i <= s[0] ; i++){
            if(s[0] % i == 0){
                fi = 1;
                break;
            }
        }
        for(int i = 2 ; i*i <= s[1] ; i++){
            if(s[1] % i == 0){
                fi = 1;
                break;
            }
        }
        if(fi){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }
    return 0;
}