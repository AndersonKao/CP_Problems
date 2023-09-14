// AC 2020/07/20 20:15:20
#include <iostream>
int main(){
    int n, i = 1;
    std::cin >> n;
    while(i <= n){
        int j = 1;
        while(j <= (n-i)){
            std::cout << ' ';
            j++;
        }
        j = 1;
        while(j <= i){
            std::cout << i;
            j++;
        }
        
        std::cout << ' ';

        j = 1;
        while(j <= i){
            std::cout << i;
            j++;
        }
        std::cout << '\n';
        i++;
    }

    return 0;
}