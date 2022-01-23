#include<bits/stdc++.h>

using namespace std;

int main() {
    vector<int> count(1000000, 1);
    count[0] = count[1] = 0;
    // the following loops: O(nlogn)
    for (int i = 2; i <= 1000000; i++)
        for (int j = i + i; j <= 1000000; j+=i)
            count[j] += i;
    int ncases;
    scanf("%d", &ncases);
    while (ncases--) {
        int x;
        scanf("%d", &x);
        if (count[x] == x)
            puts("perfect");
        else if (count[x] < x)
            puts("deficient");
        else puts("abundant");
    }
}
