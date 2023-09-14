// AC 2020/07/20 20:31:09
#include <iostream>

int main(){
    int T, Target, N;
    std::cin >> T;
    
    while(T--){
        std::cin >> Target;
        std::cin >> N;
        int i = 1;
        int data;
        while(i <= N){
            std::cin >> data;
            Target = Target - data;
            i++;
        }
        if(Target == 0)
            std::cout << "WIN\n";
        else
            std::cout << "LOSE\n";
    }


    return 0;
}