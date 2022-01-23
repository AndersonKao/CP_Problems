#include <iostream>
#include <algorithm>
using namespace std;
int seq[3];
int main(){
    int T;
    cin >> T;
    while(T--){
        for(int i = 0; i < 3; i++)
            cin >> seq[i];
        sort(seq, seq+3);
        if(seq[0] < seq[1] && seq[1] < seq[2]){
            cout << "NO\n";
        }else if(seq[0] == seq[1] && seq[1] < seq[2]){
            cout << "NO\n";
        }else if(seq[0] == seq[1] && seq[1] == seq[2]){
            cout << "YES\n";
            cout << seq[0] << ' ' << seq[0] << ' ' << seq[0] << '\n';
        }else{
            cout << "YES\n";
            cout << seq[2] << ' ' << seq[0] << ' ' << seq[0] << '\n';
        }
    }
    return 0;
}