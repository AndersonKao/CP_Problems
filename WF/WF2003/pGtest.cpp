#include <bits/stdc++.h>
using namespace std;

uint16_t rotl16a(uint16_t x, uint16_t n)
{
	return (x << n) | (x >> (16-n));
}

#define debug(x) cout << #x << ": " << hex << x << endl;
int main(){
	uint16_t x, ans;
	ans = 0;
	uint16_t lomask = ((1u << 8) - 1u);
	uint16_t himask = ~lomask; // (((1u << 8) - 1u) << 8);
	cout << hex << lomask << endl;
	cout << hex << himask << endl;
	while(cin >> hex >> x){
		if(x == 0x87)
			break;
		cout << "input: "<< hex << x << endl;
		ans = rotl16a(ans, 1);
/*
		uint16_t lo = ans & lomask;
		debug(ans);
		debug(lo);
		lo += x;	
		lo = lo & lomask;
		debug(lo);
		ans = (ans & himask) + lo;	
*/
		ans += x;
		cout << hex << ans << endl;	
	}
	return 0;
}
