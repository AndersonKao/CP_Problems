// AC Aug/16/2020 22:15UTC+8
#include <cstdio>
#include <cmath>
using namespace std;
int n, k;
char str[100005];
char ans[100005];
int main(){
    scanf("%d %d", &n, &k);
    scanf("%s", str);
    ans[n] = '\0';
    int i;
    for (i = 0; i < n; i++){
        ans[i] = str[i];
        if(k == 0)
            continue;
        if((str[i] - 'a') < ('z' - str[i])){
            while(ans[i] != 'z' && k != 0){
                ans[i]++;
                k--;
            }
        }else{
            while(ans[i] != 'a' && k != 0){
                ans[i]--;
                k--;
            }
        }
    }
    if(k != 0)
        printf("-1\n");
    else
        printf("%s\n", ans);
    // int testans = 0;
    // for (int i = 0; i < n; i++){
    //     testans += abs((int)str[i] - (int)ans[i]);
    // }
        // printf("%d\n", testans);
        return 0;

}