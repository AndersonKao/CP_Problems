// AC 2020/04/24 08:44:05
#include <iostream>

int ladder(int n);


int main()
{
	int n;
	std::cin >> n;
	std::cout << ladder(n) << '\n';
	return 0;
}
/* 你的code會放在這邊 */
int ladder(int n){
    if(n <= 0)
        return 0;
    if(n == 1)
        return 1;
    if(n == 2)
        return 2;
    if(n == 3)
        return 4;
    return ladder(n-1) + ladder(n-2) + ladder(n-3);
}

