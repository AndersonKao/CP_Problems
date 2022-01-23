#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        int seqs[4];
        for(int i = 0; i < 4; i++)
            cin >> seqs[i];
        int tomini = min(seqs[0], min(seqs[1],seqs[2]));
        for(int i = 0; i < 3; i++)
            seqs[i] -= tomini;
        seqs[3] += 3 * tomini;
        int counter = 0;
        for(int i = 0; i < 4; i++){
            if(seqs[i] & 1)
                counter++;
        }
        if(counter <= 1){
            cout << "Yes\n";
            continue;
        }
        if(!tomini){
            cout << "No\n";
            continue;
        }
        for(int i = 0; i < 3; i++)
            seqs[i] += 1;
        seqs[3] -= 3;
        counter = 0;
        for(int i = 0; i < 4; i++){
            if(seqs[i] & 1)
                counter++;
        }
        if(counter <= 1){
            cout << "Yes\n";
            continue;
        }
        cout << "No\n";
    }
    return 0;
}