#include <bits/stdc++.h>
using namespace std;

template <typename T>
using vec = vector<T>;
#define eb emplace_back
int main()
{
    string str;
    int caseN = 1;
    while (cin >> str)
    {
        if(str == "end")
            break;
        vec<char> Vs;

        for(char & ch: str){
            int sti = -1;
            for (int i = 0; i < Vs.size(); i++){
                if(ch <= Vs[i]){
                    if(sti == -1)
                        sti = i;
                    else if (Vs[sti] > Vs[i])
                    {
                        sti = i;
                    }
                }
            }
            if(sti == -1){
                Vs.eb(ch);
            }
            else{
                Vs[sti] = ch;
            }
        }
        cout << "Case " << caseN++ << ": " << Vs.size() << endl;
    }

    return 0;
}