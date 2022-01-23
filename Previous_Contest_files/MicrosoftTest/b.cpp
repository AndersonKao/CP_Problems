#include <iostream>
#include <string>
#include <stack>
using namespace std;

char type[3][2] = {{'(',')'},{'[',']'},{'{','}'}};

int findtype(char a){
    for(int i = 0 ;i < 3; i++){
        for(int j = 0;j<2;j++){
            if(a == type[i][j]){
                return i;
            }
        }
    }
}

int main() 
{
	int N;
	cin >> N;
    string str;
	while(N--){
        str = "";
        cin >> str;
        stack <char> ST;
        
        for(int i =0;i< str.length();i++){
            if(ST.empty()){
                ST.push(str[i]);
            }else{
                char test = ST.top();
                int type1,type2;
                type1 = findtype(str[i]);
                type2 = findtype(test);
                // cout << test << str[i] << type1 << type2 << endl;
                if(type1 == type2 && type[type1][0] == test){
                    ST.pop();
                }else{
                    ST.push(str[i]);
                }
            }
        }
        if(!ST.empty())
            cout << "false\n";
        else
            cout << "true\n";
    }
	return 0;
}
/*
5
()
()[]{}
(]
([)]
{[]}
*/ 
/*
1
} 
*/
/*
2
[}){)}]
({})
*/