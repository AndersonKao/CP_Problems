#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int Num;
int neck[105];
int brace[105];
int main(){
    int T;
    cin >> T;

    while(T--){
        cin >> Num;
        memset(neck,0,sizeof(neck));
        memset(brace,0,sizeof(brace));
        for(int i =0;i< Num;i++){
            cin >> neck[i];
        }
        for(int i=0;i<Num;i++){
            cin >> brace[i];
        }
        sort(neck,neck+Num);
        sort(brace,brace+Num);
        for(int i =0;i< Num;i++){
            cout << neck[i];
            if(i<Num-1)
                cout << " ";
        }
        cout << "\n";
        for(int i=0;i<Num;i++){
            cout << brace[i];
             if(i<Num-1)
                cout << " ";
        }
        cout << "\n";

    }
    return 0;
}