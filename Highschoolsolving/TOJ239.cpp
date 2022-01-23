// AC 2019-10-21 16:30:37
#ifndef EVAL
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
int arr[1000002] = {0};
int Answer(int N,int P,int *H,int *L,int *R,int *V);

int main()
{
	const int maxN = 1000000;
	const int maxP = 1000000;
	int *H = new int[maxN];
	int *L = new int[maxP];
	int *R = new int[maxP];
	int *V = new int[maxP];
	int N,P;
	while( cin>>N>>P )
	{
		for(int i=0;i<N;++i)
			cin>>H[i];
		for(int i=0;i<P;++i)
			cin>>L[i]>>R[i]>>V[i];
        for (int i = 0; i < N;i++)
            cout << H[i] << " ";
        cout << endl;

        cout << Answer(N, P, H, L, R, V) << endl;
        for (int i = 0; i < N;i++)
            cout << H[i] << " ";
        cout << endl;
	}
}
#endif
/*================================================================*/
/*================================================================*/
/*================================================================*/
/*================================================================*/
/*Write Your Program Here*/
/*Notice: You should include header for youself*/

int Answer(int N,int P,int *H,int *L,int *R,int *V)
{
	
    int arr[1000002] = {0};
    for (int i = 0; i < P;i++){
        arr[L[i]-1]+=V[i];
        if(R[i]<N)
        arr[R[i]] -= V[i];
    }
    H[0] += arr[0];
    int max = H[0], min = H[0];
    for (int i = 1; i < N;i++){
        arr[i] = arr[i] + arr[i - 1];
        H[i] += arr[i];
        if(max<H[i])
            max = H[i];
        if(min>H[i])
            min = H[i];
    }
        return max-min;
}