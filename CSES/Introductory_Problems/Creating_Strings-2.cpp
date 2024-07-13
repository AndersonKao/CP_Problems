#include <bits/stdc++.h>
using namespace std;
#define al(a) a.begin(), a.end()

int cnt[26];
string str;
char ans[9];
int number = 0;

void DFS(size_t depth, bool print){
	if(depth == str.length()){
		if(print)
			cout << ans << endl;
		else
			number++;
		return;
	}

	for(int ch = (int)'a'; ch <= (int)'z'; ch++){
		if(cnt[ch - 'a'] > 0){
			cnt[ch - 'a']--;
			ans[depth] = ch;
			DFS(depth+1, print);
			cnt[ch - 'a']++;
		}
	}
}

int main(){
	
	cin >> str;
	ans[str.length()] = '\0';

	for(size_t i = 0 ; i < str.length(); i++){
		cnt[(int)(str[i] - 'a')]++;
	}
	DFS(0, false);
	cout << number << endl;
	DFS(0, true);
	return 0;
}
