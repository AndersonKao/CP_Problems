#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;
vec<int> seq;
vec<int> seq2;
bool sol = false;
int main(){
	int T;
	cin >> T;
/*
	ofstream myfile;
	ofstream defile;
	myfile.open("output.txt");	
	defile.open("debug.txt");
*/
	if(T== -1){
		cout << "WRong!?\n";
		return 0;
	}
	while(T--){
		sol = false;
		int N;
		cin >> N;
		if(N == -1){
			cout << "wrong answer\n";
			return 1;
		}
		vec<int> ANS;
		seq.clear(), seq2.clear();
		int numTwo = min(30, N);
		REP(i, numTwo){
			cout << (1 << i) << " ";	
//			myfile << (1 << i) << " ";	
			seq2.eb(1 << i);
		}
//		cout << "goto seq: \n";
		for(int i = 3, cnt = 0; (cnt < N-numTwo) && i <= 1000000000; i++){
			if(i&1){
				cout << i << " ";		
				//myfile << i << " ";	
				cnt++;	
				seq.eb(i);
			}
		}
		cout << endl;
		cout.flush();
		int data;
		REP(i, N){
			cin >> data;
			//myfile << data << " ";	
			if(data == -1){
				cout << "wrong answer\n";
				break;
			}
			seq.eb(data);
		}
		if(data == -1)
			return 1;
		ll lsum, rsum;
		lsum = rsum = 0;	
		sort(al(seq), greater<int>());
		REP(i, (int)seq.size()){
			if(lsum <= rsum){
				ANS.eb(seq[i]);
				lsum += seq[i];
			}	
			else{
				rsum += seq[i];
			}
		}	
		ll diff = lsum - rsum;
		//debug(diff);
		//defile << "diff : " << diff << endl;
		string bitstr;
		for(int i = 29; i >= 0; i--){
			if(abs(diff) & (1 << i)){
				bitstr += "1";	
			}else
				bitstr += "0";
		}
		//debug(bitstr);
		//defile << "bitstr : " << bitstr << endl;
		//string str2, str1;
		if(diff < 0){
			for(int i = 0; i < (int)bitstr.length(); i++){
				if((i == 0) || (i > 0 && bitstr[i-1] == '1'))
						ANS.eb(seq2[29-i]);	
/*
				if((i == 0) || (i > 0 && bitstr[i-1] == '1')){
						str1 += "1";
						str2 += "0";
				}else{
						str1 += "0";
						str2 += "1";	
				}
*/

			} 
		}else{
			for(int i = 0; i < (int)bitstr.length(); i++){
				if((i > 0 && bitstr[i-1] == '0'))
						ANS.eb(seq2[29-i]);	
/*
				if((i > 0 && bitstr[i-1] == '0')){
						str1 += "1";
						str2 += "0";
				}else{
						str1 += "0";
						str2 += "1";
				}
*/
			} 
		}	
		//defile << "str1 :   " << str1 << endl;
		//defile << "str2 :   " << str2 << endl;
		//ofstream myans;
		//myans.open("myans.txt");
//		myans << "cat \n\n";
		REP(i, (int)ANS.size()){
			cout << ANS[i] << (i == (int)ANS.size()-1? "\n" : " ");
		//	myans << ANS[i] << (i == (int)ANS.size()-1? "\n" : " ");
		}
		//myans.close();
		
		cout.flush();
	}
//myfile.close();
}
