#include <bits/stdc++.h>
using namespace std;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
string str1, str2;
bool valid(char a, char b){
    return ((a - '0') + (b - '0')) <= 3;
}
int solve(){

    unsigned start = 0;
    unsigned ans = str1.length() + str2.length();
    for (start = 0; start < str1.length(); start++)
    {
        bool solved = true;
        for (unsigned i = start; i < str1.length() && (i - start) < str2.length(); i++){
            if(!valid(str1[i], str2[i-start]))
            {
                solved = false;
                break;
            }
        }
        if(solved)
        {
            ans = min(ans, max(str1.length(), str2.length() + start));
        }
    }
    swap(str1, str2);
    for (start = 0; start < str1.length(); start++)
    {
        bool solved = true;
        for (unsigned i = start; i < str1.length() && (i - start) < str2.length(); i++){
            if(!valid(str1[i], str2[i-start]))
            {
                solved = false;
                break;
            }
        }
        if(solved)
        {
            ans = min(ans, max(str1.length(), str2.length() + start));
        }
    }
    return ans;
}
int main()
{
    while(cin >> str1 >> str2)    
    {
        cout << solve() << "\n";
    }
    return 0;
}