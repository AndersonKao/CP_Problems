#include <bits/stdc++.h>
using namespace std;

long long seq[200001];
int main(){
    int n;
    long long x;
    cin >> n >> x;
    for (int i = 0; i < n; i++)
        cin >> seq[i];
    unsigned pt1, pt2;
    pt1 = pt2 = 0;
    long long cur = seq[0];
    long long ans = 0;
    while(pt1 < n && pt2 < n){
        while(pt2 + 1 < n && cur + seq[pt2 + 1] <= x){
            cur += seq[pt2 + 1];
            pt2++;
//            cout << "incre pt2 = " << pt2 << "\n";
        }
        if(cur == x)
            ans++;
        cur -= seq[pt1];
        pt1++;
 //       cout << "incre pt1 = " << pt << "\n";
    }
    cout << ans << endl;
    return 0;
}