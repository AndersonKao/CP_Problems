#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    while(cin >> N){
        cout << N << endl;
        if(N == 0)
            break;
        int x, y, z;
        for (int i = 0; i < N - 1; i++)
        {
            cin >> x >> y >> z;
            cout << x << " " << y << " " << z << "\n";
        }
    }
    return 0;
}