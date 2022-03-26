#include <bits/stdc++.h>
using namespace std;
#define al(a) a.begin(), a.end()
int main(){
	string str;
	cin >> str;
	int cnt = 0;
	sort(al(str));
	do{
		cnt++;
	}while(next_permutation(al(str)));
	cout << cnt << endl;
	do{
		cout << str << endl;
	}while(next_permutation(al(str)));
	return 0;
}
