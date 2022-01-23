#include <iostream>
using namespace std;
bool seq[3][100005] = {true}; 
int N,Q;
bool testing(){
    int r = 1 ,c = 1;
    if(seq[1][1] == false || seq[2][N] == false)
            return false;
    while(c != N){
        if(seq[r][c+1])
            c+=1;
        else
        {
        // cout << "R:" << r << "C:" << c << endl;
            int t = (r==1 ? 2 : 1);
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
        }else{
            cout << "No\n";
        }
    }
    return 0;
}