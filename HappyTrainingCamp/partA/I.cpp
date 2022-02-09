#include <bits/stdc++.h>
using namespace std;

int T;

string str1, str2;
int main(){
    //cin.tie(0);
    //ios_base::sync_with_stdio(false);
    while(cin >> str1 >> str2){
        unsigned index, index2;
        index = index2 = 0;
        while(index < str1.length() && index2 < str2.length()){
            while(index2 < str2.length() && str1[index] != str2[index2])
                index2++;
            if(index2 == str2.length())
                break;
            index++;
            index2++;
        }
        if(index < str1.length())
            cout << "No\n";
        else
            cout << "Yes\n";
        // YES  NO
    }


    return 0;
}