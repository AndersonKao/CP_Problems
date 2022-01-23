// JOE is on TV!
// AC Jan/19/2020 22:21UTC+8
#include <iostream>
using namespace std;
int main(){
    int K;
    cin >> K;
    double ans = 0;
    for(int i = K ;i>0;i--){
        ans += (double)1/i;
    }
    printf("%.12lf\n",ans);
    return 0;
}