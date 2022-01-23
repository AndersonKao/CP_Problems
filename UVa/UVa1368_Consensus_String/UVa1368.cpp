// AC 2019-10-21 13:50:01
#include <iostream>
using namespace std;
char str[51][1001];
char strans[1001];
int sum[200];
void init(){
    sum[(int)'G'] = 0;
    sum[(int)'C'] = 0;
    sum[(int)'A'] = 0;
    sum[(int)'T'] = 0;
}
void count(char A){
    sum[(int)A]++;
}
int main(){
    int T,m,n;
    cin >> T;
    while(T--){
        cin >> m >> n;
        for (int i = 0; i < m;i++)
            cin >> str[i];
        for (int i = 0; i < n;i++)
        {
            init();
            for (int j = 0; j < m;j++)
            {
                sum[(int)str[j][i]]++;
            }
            char K;
            int max = 0;
            for (int i = 0; i < 200;i++){
                if(max < sum[i])
                    max = sum[i];
            }
            if(max == sum[(int)'T'])
                K = 'T';
            if(max == sum[(int)'G'])
                K = 'G';
            if(max == sum[(int)'C'])
                K = 'C';
            if(max == sum[(int)'A'])
                K = 'A';
            strans[i] = K;
        }
        int errors = 0;
        for (int i = 0; i < m;i++)
            for (int j = 0; j < n;j++)
                if(str[i][j] != strans[j])
                    errors++;
                strans[n] = '\0';
        cout << strans << '\n' << errors << '\n';
    }
    return 0;
}

/*
5 8
TATGATAC
TAAGCTAC
AAAGATCC
TGAGATAC
TAAGATGT
4 10
ACGTACGTAC
CCGTACGTAG
GCGTACGTAT
TCGTACGTAA
6 10
ATGTTACCAT
AAGTTACGAT
AACAAAGCAA
AAGTTACCTT
AAGTTACCAA
TACTTACCAA
*/