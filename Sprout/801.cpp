// AC 2020/07/20 20:20:27
#include <iostream>

int main(){
    int steps = 0;
    int n;
    std::cin >> n;
    while(n != 1){
        if(n%2==1){
            n = n * 3 + 1;
        }else{
            n = n / 2;
        }
        steps++;
    }
    std::cout << steps ;
    return 0;
}