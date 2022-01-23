#include <iostream>
#include <cmath>

using namespace std;

long long seq[100005];

int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> seq[i];

    int bi = 0;
    bool flag = false;
    int twonum = 0;
    long long totalsum = 0;
    for (int i = 0; i < n; i++){
        totalsum += seq[i];
        if(seq[i] % 2 == 1){
            bi++;
        }else{
            if(seq[i] != 2){
                flag = true;
                break;
            }else{
                twonum++;
                if(twonum >= 2){
                    flag = true;
                    break;
                }
            }
        }
    }
    if(bi >= 2 && totalsum > 3){
        flag = true;
    }

    if(n == 1 && seq[0] > 3 && (seq[0] % 2 == 1)){
        for (long long i = 3; i <= sqrt(seq[0]) + 1; i++){
            if(seq[0] % i == 0){
                flag = true;
                break;
            }
        }
    }
    if(!flag){
        for (long long i = 3; i <= sqrt(totalsum) + 1; i++){
            if(totalsum % i == 0){
                flag = true;
                break;
            }
        }
    }
    if(flag)
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}