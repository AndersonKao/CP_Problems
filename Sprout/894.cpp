// AC 2020/08/12 11:01:42
#include <iostream>
#include <cstring>
using namespace std;
char str1[105], str2[105];
char ansstr[220];
int len1, len2;
int main(){
    cin >> str1 >> str2;
    cin >> len1 >> len2;
    strncpy(ansstr, str1, len1);
    strncat(ansstr, str2, len2);
    for(int i = 0; i < 3; i++)
        cout << ansstr << endl;
    return 0;
}