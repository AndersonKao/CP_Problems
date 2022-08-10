#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll inv = 0;
void merge(int* arr, int p, int q, int r){
	int * tmp = new int[r - p + 1];		
	int i = 0, pi = p, ri = q+1;
	int Rlen = 0;
	while(pi <= q && ri <= r){
		if(arr[pi] <= arr[ri]){
			tmp[i++] = arr[pi++];
			inv += Rlen;
		}else{
			tmp[i++] = arr[ri++];
			Rlen++;
		}
	}
	while(pi <= q){
		tmp[i++] = arr[pi++];	
		inv += Rlen;
	}
	while(ri <= r){
		tmp[i++] = arr[ri++];
	}
	for(int i = 0; i < r-p+1; i++){
		arr[p+i] = tmp[i];
	}
	delete [] tmp;
}
void mergeSort(int *arr, int p, int r)
{
	if(p < r){
		int q = (p+r)/2;	
		mergeSort(arr, p, q);
		mergeSort(arr, q+1, r);
		merge(arr, p, q, r);	
	}
}

int main(){
	int N;
	while(cin >> N){
		if(N == 0)
			break;
		inv = 0;
		int * arr = new int[N];
		for(int i = 0; i < N; i++)
			cin >> arr[i];
		mergeSort(arr, 0, N-1);
/*		for(int i = 0; i < N; i++)
			cout << arr[i] << " ";
		cout << endl;*/
		cout << inv << endl;
		delete [] arr;
	}
	return 0;
}
