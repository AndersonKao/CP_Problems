// AC 2019-10-21 13:56:03
#include <iostream>
#include <set>
#include <sstream>
#include <string>
using namespace std;

set<string> dict; // string 集合

int main(){
    string s, buf;
    while (cin >> s){
        for (int i = 0; i < s.length(); i++){
            if (isalpha(s[i]))
                s[i] = tolower(s[i]);
            else
                s[i] = ' ';
        }
        stringstream ss(s);
        while(ss >> buf)
            dict.insert(buf);
    }
    for (set <string>::iterator it = dict.begin(); it != dict.end(); ++ it)
        cout << *it << "\n";
        return 0;
}
/*Adventures in Disneyland

Two blondes were going to Disneyland when they came to a fork in the
road. The sign read: "Disneyland Left."

So they went home.*/