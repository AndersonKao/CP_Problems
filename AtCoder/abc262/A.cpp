#include <iostream>
using namespace std;

int main(){
	int Y;
	cin >> Y;
	for(int i = 0; i < 4; i++){
		if((Y + i) % 4 == 2){
			cout << Y + i << endl;
			break;
		}
			
	}
	return 0;
}
