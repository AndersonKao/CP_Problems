#include <bits/stdc++.h>
using namespace std;

map<string, int> M;
int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++){
        string str;
        cin >> str;
        if(M[str]){
            cout << str << "(" << M[str] << ")\n";
        }
        else
            cout << str << endl;
        M[str]++;
    }
        return 0;
}