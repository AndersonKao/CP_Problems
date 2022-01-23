#include <iostream>
using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        int a, b;
        cin >> a >> b;
        int c = b % (a-1);

        cout << (b / (a-1)) * a + (c == 0 ? -1 : c) << '\n';
    }

    return 0;
}