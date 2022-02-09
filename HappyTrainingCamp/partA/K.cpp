#include <bits/stdc++.h>
using namespace std;

int T;

char mirrors[256];
bool isPalin(string &str){
    for (int i = 0; i < str.length()/2; i++){
        if(str[i] != str[str.length() - i - 1]){
            return false;
        }
    }
    return true;
}
bool isMirror(string &str){
    string str2("");
    for (int i = str.length() - 1; i >= 0; i--){
        if(mirrors[str[i]] == 'n')
        {
//            cout << "str[i = " << i << "] = " << str[i] << " has no mirror\n";
            return false;
        }
        str2 += mirrors[str[i]];
    }
 //   cout << "str2: " << str2 << endl;
    if(str2 == str){
        return true;
    }
    return false;
}

void solve(string & str){
    bool isP, isM;
    isP = isPalin(str);
    isM = isMirror(str);
    cout << str;
    if(isP && isM){
        cout << " -- is a mirrored palindrome.\n\n";
    }
    else if(!isP && isM){
        cout << " -- is a mirrored string.\n\n";
    }
    else if(isP && !isM){
        cout << " -- is a regular palindrome.\n\n";
    }
    else if(!isP && !isM){
        cout << " -- is not a palindrome.\n\n";
    }
}

void buildTable(){
    fill(mirrors, mirrors + 256, 'n');
    mirrors['A'] = 'A';
    mirrors['E'] = '3';
    mirrors['H'] = 'H';
    mirrors['I'] = 'I';
    mirrors['J'] = 'L';
    mirrors['L'] = 'J';
    mirrors['M'] = 'M';
    mirrors['O'] = 'O';
    mirrors['S'] = '2';
    mirrors['T'] = 'T';
    mirrors['U'] = 'U';
    mirrors['V'] = 'V';
    mirrors['W'] = 'W';
    mirrors['X'] = 'X';
    mirrors['Y'] = 'Y';
    mirrors['Z'] = '5';
    mirrors['1'] = '1';
    mirrors['2'] = 'S';
    mirrors['3'] = 'E';
    mirrors['5'] = 'Z';
    mirrors['8'] = '8';
    /*
    for (char ch = 'A'; ch <= 'Z'; ch++){
        cout << ch << ": " << mirrors[ch] << "\n";
    }
    for (char ch = '1'; ch <= '9'; ch++){
        cout << ch << ": " << mirrors[ch] << "\n";
    }
    */
}


int main(){
    // so what if I use cin.tie(0)??
    //cin.tie(0);
    //ios_base::sync_with_stdio(false);
    buildTable();
    string str;
    while(cin >> str){
        solve(str);
    }

    return 0;
}