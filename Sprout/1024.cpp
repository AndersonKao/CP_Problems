// AC 
#include <iostream>
#include <iomanip>
#include <random>
using namespace std;
int main(){
    double c = 0.0;
    double x, y;
    int t = 1e7;
    for (int i = 0; i < t; i++){
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if(x * x + y * y <= 1)
            c++;
    }
    double p2 = 4 * c / t;
    double p1 = 1;
    int k;
    cin >> k;
    for (int i = 1; i <= k; i++){
        p1 = p1 * 4 * i * i / (2 * i - 1) / (2 * i + 1);
    }
    p1 = p1 * 2;
    // cout << p1 << endl;
    // cout << p2 << endl;
    cout << fixed << setprecision(2) <<  abs(p1 - p2) << endl;

    return 0;
}