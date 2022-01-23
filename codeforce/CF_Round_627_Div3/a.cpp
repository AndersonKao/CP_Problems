#include <iostream>
using namespace std;

int height[105];

int main(){
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        for(int i=0;i<N;i++)
            cin >> height[i];
        bool flag = true;
        while(flag){

            for(int i=0;i<N;i++)
            {
                if(height[i] == 0){
                    flag = false;
                }
            }
            if(flag)
                for(int i=0;i<N;i++)
                    height[i]--;
        }
        int even = 0,odd = 0;
        bool aflag = true;
        for(int i=0;i<N;i++)
            if(height[i] % 2 == 1){
                aflag = false;
                break;
            }
        if(!aflag)
            cout << "NO\n";
        else
            cout << "YES\n";
       
    }
    return 0;
}