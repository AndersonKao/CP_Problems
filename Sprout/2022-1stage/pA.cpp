#include <bits/stdc++.h>
using namespace std;

int main(){
    int x[2], y[2];
    cin >> x[0] >> y[0] >> x[1] >> y[1];
    
    int w = ((-y[1]) * (x[0] - x[1])) / (y[0]-y[1]) + x[1];
    int h =((-x[1]) * (y[0] - y[1])) / (x[0] - x[1]) + y[1];
    if(w * h < 0)
        cout << w * h / -2 << endl;
    else
        cout << w * h / 2 << endl;
    return 0;
}