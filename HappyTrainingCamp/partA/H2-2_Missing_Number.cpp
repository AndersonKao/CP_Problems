#include <bits/stdc++.h>
using namespace std;

int T;

bool appear[200000] = {false};
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    unsigned N;
    cin >> N;
    unsigned data;
    for (unsigned i = 0; i < N - 1; i++){
        cin >> data;
        appear[data - 1] = true;
    }
    for (unsigned i = 0; i < N; i++)
        if(appear[i] == false){
            cout << i + 1 << "\n";
            break;
        }
    return 0;
}