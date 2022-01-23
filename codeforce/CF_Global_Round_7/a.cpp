#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int seq [3] = {23,29,31};
int realone = -1;
bool valid(int a,int n){
    stringstream ss;
    string str;
    ss << a;
    ss >> str;
    if(n != str.length())
        return false;
    for(int i = 0;i<str.length();i++)
        if(str[i] == '0' || str[i] == '1')
            return false;
    
    for(int i =0;i<str.length();i++){
        if(a % (str[i] - 48) == 0){
            return false;
        }
    }
    return true;
}

void dp(int ans,int n){
    if(realone != -1)
        return ;
    if(valid(ans,n)){
        realone = ans;
        return;
    }
    stringstream ss;
    string str;
    ss << ans;
    ss >> str;
    if(str.length() > n)
        return ;
    int togo = ans;
    for(int i = 0 ;i<3;i++){
            togo *= seq[i];
            cout << "going to test" << togo << endl;
            dp(togo,n);
            togo /= seq[i];
    }
}

int main(){
    int T,N;
    cin >> T;
    while(T--){
        cin >> N;
        realone = -1;
        if(N == 1){
            cout << "-1\n";
        }else if(N==2){
            cout << 23 << endl;
        }else{
            dp(1,N);
            cout << realone << endl;
        }
    }
    return 0;
}