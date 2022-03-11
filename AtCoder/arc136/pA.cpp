#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){

}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    string str;
    cin >> str;
    int Bnum = 0;
    for (int i = 0; i < N; i++){
        if(str[i] == 'A'){
            Bnum += 2;
        }else if(str[i] == 'B'){
            Bnum++;
        }
        else if(str[i] == 'C'){
            while(Bnum > 0){
                cout << "B";
                Bnum -= 1;
            }
            cout << "C";
        }
        while(Bnum>=2){
            cout << "A";
            Bnum-= 2;
        }
        
    }
    while(Bnum > 0){
        cout << "B";
        Bnum -= 1;
    }
    cout << endl;
    return 0;
}