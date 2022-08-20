#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-4;
int fcmp(double a, double b){
	if(abs(a-b) < eps)
		return 0;
	return (a > b) * 2 - 1;
}

int main(){
	fstream fs;
	fstream f2;
	fs.open("pGsam.in", std::fstream::in);
	f2.open("pGsam2.in", std::fstream::out);
	int n;
	while(fs >> n){
		if(n == 0) break;
		f2 << n << endl;
		for(int i = 0; i< n;i++){
			int t;
			fs >> t ;
			f2 << t << " ";
		}
		f2 << endl;
	}
	fs.close();
	f2.close();
	fs.open ("pGsam.out", std::fstream::in); 
	double tmp;
	vector<double> in2, in1;
	cout << "in1\n";
	while(fs >> tmp){
		cout << tmp << endl;
		in1.push_back(tmp);
	}
	fs.close();
	fs.open ("pG.out", std::fstream::in); 
	cout << "in2\n";
	while(fs >> tmp){
		cout << tmp << endl;
		in2.push_back(tmp);
	}
	fs.close();
	for(int i = 0; i < in1.size() && i < in2.size(); i++){
		
		if(fcmp(in1[i], in2[i]) != 0){
			cout << "Case " << i +1 << endl;
			cout << fixed << setprecision(10) << in1[i] << endl;
			cout << fixed << setprecision(10) << in2[i] << endl;
		}
	}

	return 0;
}
