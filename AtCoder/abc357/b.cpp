#include <bits/stdc++.h>
using namespace std;

int main()
{
string str;
cin >> str;
	int u = 0, l = 0;
	for(int i = 0; i < str.length(); i++){
		if(isupper(str[i]))
			u++;
		else if(islower(str[i]))
			l++;
	}
	for(int i = 0; i < str.length(); i++){
		if(u > l && islower(str[i])){
			cout << (char)(str[i] - ('a' - 'A'));
		}
		else if(u <= l && isupper(str[i])){

			cout <<(char)(str[i] + ('a' - 'A'));
		}
		else{
			cout << str[i];

		}
	}
  return 0;
}
