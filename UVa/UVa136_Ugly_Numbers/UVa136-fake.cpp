#include <iostream>
using namespace std;
int main(){
    int cnt = 1;
    long long x = 1;
    while(++x){
        long long num = x;
        while(num % 2 == 0)
            num /= 2;
        while(num % 3 == 0)
            num /= 3;
        while(num % 5 == 0)
            num /= 5;
        if(num == 1) 
        {
            cnt++;
        }
        if(cnt == 1500){
            printf("The 1500'th ugly number is %lld.\n", x);
            break;
        }
    }
    return 0;
}