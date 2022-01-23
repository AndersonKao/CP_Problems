#include <iostream>
using namespace std;
long long thing[105][2];
bool thingtaken[105] = {1};
int N,C,K;
long long ans = 0;

void dp(long long Cvol,long long K,long long Cvalue){
    bool flag = false;
    for(int i = 0;i<N;i++){
        if(Cvol - thing[i][0] >= 0){
            flag = true;
            break;
        }
    }
    if(flag == false){
        // cout << "testing\n";
        // cout << Cvalue << endl;
        ans = ans > Cvalue ? ans : Cvalue;
    }
    for(int i = 0;i<N;i++){
        if(Cvol - thing[i][0] >=K){
            thingtaken[i] = false;
            dp(Cvol - thing[i][0] - K,K,Cvalue + thing[i][1]);
            thingtaken[i] = true;
            // flag = true;
        }else if(Cvol - thing[i][0] >= 0){
            thingtaken[i] = false;
            dp(Cvol - thing[i][0],K,Cvalue + thing[i][1]);
            thingtaken[i] = true;
            // flag  = true;
        }
    }
}

int main(){
    cin >> N >> C >> K;
    for(int i = 0;i<N;i++){
        cin >> thing[i][0];
    }
    for(int i=0;i<N;i++)
        cin >> thing[i][1];
    ans = 0;
    dp(C,K,0);
    cout << ans << endl;
    return 0;
}