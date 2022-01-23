#include <iostream>
using namespace std;
#define UINT unsigned short int
int XORab(UINT a, UINT b){
    int counter = 0;
    while(a | b){
        if(!((a%2) ^ (b%2))){
            counter++;
        }
        a  = a >> 1;
        b = b >> 1;
    }
}
int main(){
    // cout << (6 >> 1) << endl;
    cout << XORab(6,2);
    return 0;
}