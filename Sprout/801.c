#include <stdio.h>

int main(){
    int Number;
    int Counter = 0;
    scanf("%d", &Number);

    while(Number != 1){
        if(Number % 2 == 1){
            Number = Number * 3 + 1;
        }else{
            Number = Number / 2;
        }
        Counter = Counter + 1; // Counter++;
    }
    printf("%d\n", Counter);
    return 0;
}