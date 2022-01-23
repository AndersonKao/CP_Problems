#include <iostream>
using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        int a,b;
        cin >> a >> b;
        if(a == b){
            cout << "0\n";
        }else if(a > b){
            if((a-b)%2 == 0){
                cout << "1\n";
            }else{
                cout << "2\n";
            }
        }else if(a < b){
            if((b-a)%2==0){
                cout << "2\n";
            }else{
                cout << "1\n";
            }

        }
    }
    return 0;
}