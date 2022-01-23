#include <iostream>
using namespace std;
typedef struct{
    int index;
    int beauty;
}database;

database beau[200005];
int Ans = 0;
int main(){
    int N;
    cin >> N;
    for(int i = 0;i<N;i++){
        beau[i].index = i;
        cin >> beau[i].beauty;
    }
    if(N == 1)
        cout << beau[0].beauty << "\n";
    else{
        for(int i=0;i<N;i++){
            if()
        }   
    }
    return 0;
}