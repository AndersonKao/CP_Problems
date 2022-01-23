#include <iostream>
using namespace std;

int seq[10] = {6,2,5,5,4,5,6,3,7,6};
int seq2[10] = {1,7,4,5,9,8};

int main(){
    unsigned long long  Num;
    cin >> Num;
    for(int i =0;i< Num;i++){
        int Max_seg; 
        cin >> Max_seg;
        unsigned long long ans = 0;
        if(Max_seg % 2 == 1){
                cout << "7"; 
                
                Max_seg -= 3;
        }
        
        while(Max_seg > 0){ 
           
           
            cout << "1";
            Max_seg -= 2;
           ans++;
        }
        cout << "\n";
        // cout << ans;
    }
    return 0;
}