#include <bits/stdc++.h>
using namespace std;

int main(){
	fstream fs;
	fs.open("Lgen.in", fstream::out);
	fs << 1 << endl;
	fs << 200000 << endl;
	for(int i = 0; i < 200000-1 ; i++){
		fs << i + 1 << " ";
	}
	fs << endl;
	for(int i = 0; i < 200000 ; i++){
		fs << 0 << " ";
	}
	fs << endl;
	

	return 0;
}

