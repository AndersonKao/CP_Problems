#include <iostream>
using namespace std;
bool seq[3][10005] = {true}; 
int N,Q;
bool testing(){
    int r =1 ,c = 1;

    while( r != 2 && c != N){
        if(seq[r][c+1])
            c+=1;
        else
        {
            int t = r==1 ? 2 : 1;
            if(seq[t][c+1] == false)
                return false;
            if(seq[t][c] == false)
                return false;
            r = t;
        }
    }
    return true;
}
int main(){
   
    cin >> N >> Q;
    for(int i=1;i<=N;i++)
        seq[1][i] = seq[2][i] = true;
    int r,c;
    for(int i=0;i<Q;i++){
        cin >> r >> c;
        seq[r][c] = !seq[r][c];
        if(testing()){
            cout << "Yes\n";
        }else
            cout << "No\n";
    }
    return 0;
}