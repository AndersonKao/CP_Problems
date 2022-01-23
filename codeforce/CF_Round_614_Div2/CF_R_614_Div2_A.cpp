#include <iostream>
using namespace std;
bool open[1000000001];
int main(){
    int T,n,s,k,tel;
    
    cin >> T;
    while(T--){
        bool cuttail = true;
        cin >> n >> s >> k;
        for(int i =1;i<=n;i++)
            open[i] = true;
        for(int i=0;i<k;i++){
            cin >> tel;
            if(tel == s)
                cuttail = false;
            open[tel] = 0;
        }
        if(cuttail){
            cout << "0\n";
            continue;
        }
        int index = 1;
        while(true){
            if((open[s+index] && s+index <= n) || (open[s-index] && s-index >=1)){
                cout << index << endl;
                break;
            }
            index++;
        }
    }   
    return 0;
}