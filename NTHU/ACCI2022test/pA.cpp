#include <bits/stdc++.h>
using namespace std;

int main(){

    string str;
    getline(cin, str);
    cout << "Hello, ";
    int i = 0;
    while (i < str.length() && str[i] == ' ')
        i++;
    for (int j = i; j < str.length(); j++)
        cout << str[j];
    cout << "!\n";

    return 0;
}