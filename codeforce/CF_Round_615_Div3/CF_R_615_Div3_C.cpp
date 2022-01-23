
// AC 01:04:06
#include <iostream>
#include <queue>
#include <stack>
#include <math.h>
using namespace std;
int main(){
    int T; cin >> T;
    while(T--){
        unsigned long long NUM;
        cin >> NUM;
        
        int ans[3];
        int index = 0;
        bool flag = true;
        int limit = sqrt(NUM);
        unsigned long long a ,b;
        a = b = 0;
        for(int i = 2;i<=limit+5;i++){
            if(NUM%i == 0){
                a = i;
                break;
            }
        }
        // cout << "a:" << a << endl;
        if(a != 0){
            NUM /=a;
            limit = sqrt(NUM);
            for(int i = a + 1;i<=limit+5;i++){
                if(NUM%i == 0){
                    b = i;
                    break;
                }
            }
        }
        if(b != 0 && NUM/b > b){
            cout << "YES\n" << a << " " << b << " " << NUM / b << "\n";
        }else
        {
            cout << "NO\n";
        }
        
    }

    return 0;
}