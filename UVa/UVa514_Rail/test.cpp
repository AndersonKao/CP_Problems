#include <queue>
#include <iostream>
std::queue<int> que;
int main(){
    que.push(1);
    std::cout << que.front() << '\n';
    // return the value of first element
    // (the next one to be pop),
    // not performing pop
    que.push(2);
    std::cout << que.back() << '\n';
    std::cout << que.front() << '\n';
    que.pop();
    // pop out the firsst element, no return 
    std::cout << que.front() << '\n';

}