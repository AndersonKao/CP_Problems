#include <iostream>
using namespace std;
int main(){
    int T, N;
    cin >> T;
    while(T--){
        cin >> N;
        for(int i = 1; i <= N; i++)
            cout << i << (i == N ? '\n': ' ');
    }
    return 0;
}