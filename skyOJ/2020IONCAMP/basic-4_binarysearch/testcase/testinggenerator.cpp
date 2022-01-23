#include <iostream>
#include <string>
using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    int K;
    int counter = 0;
    string str;
    while(T--){
        cin >> K >> str;
        counter += str.length();
    }

    cout << counter << endl;
    return 0;
}