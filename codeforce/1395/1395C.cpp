#include <iostream>
using namespace std;
int aseq[205], bseq[205];
int n, m;

bool valid(int data){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int cur = aseq[i] & bseq[j];
            if((cur | data) == data){
                break;
            }
            if(j == m-1)
                return false;
        }
    }
    return true;
}


int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> aseq[i];
    }
    for(int i = 0; i < m; i++){
        cin >> bseq[i];
    }
    for(int i = 0; i <= (1 << 9); i++){
        if(valid(i)){
            cout << i << endl;
            break;
        }
    }

    
    return 0;

}