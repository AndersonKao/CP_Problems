#include <iostream>
using namespace std;
int colN, rowN;
int stC, stR;

int main(){
    cin >> rowN >> colN;
    cin >> stR >> stC;
    cout << stR << ' ' << stC << endl;
    for(int j = 1; j <= colN; j++){
        if(j == stC) continue;
        cout << stR << " " << j << endl;
    }

    int counter = 1;
    for(int i = 1; i <= rowN; i++){
        if(i == stR) continue;
        if(counter & 1){
            for(int j = colN; j >= 1; j--){
                cout << i << ' ' << j << endl;
            }
            counter = !counter;
        }else{
            for(int j = 1; j <= colN; j++){
                cout  << i << ' ' << j << endl;
            }
            counter = !counter;
        }
    }

    return 0;
}