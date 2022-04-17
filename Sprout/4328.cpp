#include <iostream>
int walkOnMyOwnPath(int path[], int pos[], int size, int time);

int main() {
    int n, m, t;
    int path[100000] = {};
    int pos[10] = {};
    std::cin >> n >> m >> t;

    for (int i = 0; i < n; i++) {
        std::cin >> path[i];
    }

    for (int i = 0; i < m; i++) {
        std::cin >> pos[i];
    }

    int isCollide = walkOnMyOwnPath(path, pos, m, t);
    if (isCollide == -1) {
        std::cout << "Fine :)" << std::endl;
    }
    else {
        std::cout << "Fine QQ " << isCollide << std::endl;
    }
}

// your code will be put here  

int walkOnMyOwnPath(int path[], int pos[], int size, int time){
    int visited[100001];
    for(int i = 0; i <= 100000; i++)
        visited[i] = -1;
    for (int i = 0; i < size; i++){
        if(visited[pos[i]] != -1){
            return 0; // somebodies overlap at t = 0.
        }
        visited[pos[i]] = i;
    }
    bool circle = false;
    int t = 0;
    while(!circle && t <= time) {
        t++;
        circle = true;
        for (int j = 0; j < size; j++) {
            pos[j] = path[ pos[j] ];
            if (visited[pos[j]] != j) {
                if(visited[pos[j]] != -1)
                    return t;
                else{
                    visited[pos[j]] = j;
                    circle = false;
                }
            }
        }
    }
    return -1;
}