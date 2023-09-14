// AC 2020/06/30 18:39:01
#include <iostream>
using namespace std;

int red[25];
int Ans = 0;
int capacity, Num;
void recursion(int depth, int capacity){
    if(depth == Num){
        Ans++;
        return;
    }

    recursion(depth + 1, capacity); // 代表不塞這張
    if(capacity >= red[depth]) // 代表塞這張
        recursion(depth + 1, capacity - red[depth]);
}


int main(){
    cin >> Num >> capacity;
    for(int i = 0; i < Num; i++){
        cin >> red[i];
    }

    recursion(0, capacity);
    
    cout << Ans << endl;

    return 0;
}