// AC 2021-08-21 18:01:36
#include <iostream>
#include <set>
#include <map>
using namespace std;

map<int, int> M;
int seq[1000005];
int last[1000005];
int main()
{
    int T;
    cin >> T;
    int L, R;
        int ANS = 0;
    while(T--){
        M.clear();

        ANS = 0;
        int N;
        cin >> N;
        for (int i = 0; i < N; i++){
            cin >> seq[i];
            if(!M.count(seq[i]))
                last[i] = -1;
            else
                last[i] = M[seq[i]];
            M[seq[i]] = i;
        }
        L = 0;
        R = 0;
        while(R != N){
            while(R < N && last[R] < L)
            {
                R++;
            }
            ANS = max(R - L, ANS);
            L++;
        }
        
    cout << ANS << endl;
    }
}