#include <cstdio>
#include <cstring>
#define max(a, b) ((a) > (b) ? (a) : (b))
char ch;
int main(){
    scanf("%c", &ch);
    char pre = ch;
    unsigned ans = 1;
    unsigned cur = 1;
    while(~scanf("%c", &ch)){
        if(pre == ch){
            cur = 0;
        }
        pre = ch;
        cur++;
        ans = max(ans, cur);
    }
    printf("%u\n", ans);

    return 0;
}