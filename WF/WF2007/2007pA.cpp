#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define eb emplace_back
enum type
{
    A = 0,
    B = 1,
    AB = 2,
    O = 3
};
template <typename T>
using vec = vector<T>;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
using pti = pair<type, int>;
vec<vec<vec<int>>> shojo = {
    {{A, O}, {AB, A, B, O}, {AB, A, B}, {A, O}},
    {{AB, A, B, O}, {B, O}, {AB, A, B}, {B, O}},
    {{AB, A, B}, {AB, A, B}, {AB, A, B}, {A, B}},
    {{A, O}, {B, O}, {A, B}, {O}},
};
vec<vec<vec<int>>> pos = {
    {{0, 1}, {0, 1}},
    {{0, 1}, {0}}
};

void printit(vec<int> &ansS, vec<int> &ansP){
    if(ansS.empty() || ansP.empty()){
        cout << "IMPOSSIBLE";
        return;
    }
    sort(ansS.begin(), ansS.end(), [](int &a, int &b)
         { return (-a) < (-b); });
    if(ansS.size() != 1 || ansP.size() != 1)
        cout  << "{";
    for (int i = 0; i < ansS.size(); i++)
    {
        for (int j = 0; j < ansP.size(); j++){
            if((i == 0 && j == 0) == false){
                cout << ", ";
            }
            if(ansS[i] == A){
                cout << "A";
            }
            else if(ansS[i] == B){
                cout << "B";
            }
            else if(ansS[i] == AB){
                cout << "AB";
            }
            else
                cout << "O";
            cout << (ansP[j] ? "+" : "-");
        }
    }
    if(ansS.size() != 1 || ansP.size() != 1)
        cout << "}";
}

int main()
{
    int caseN = 1;
    string p[3];
    while(cin >> p[0] >> p[1] >> p[2]) {
        string test = p[0] + p[1] + p[2];
        if (test == "END")
            break;
        vec<pti> bp(3);
        REP(i, 3){
            if(p[i] == "?")
                continue;
            if(p[i].length() == 3){
                bp[i].first = AB;
            }else{
                switch (p[i][0])
                {
                case 'O':
                    bp[i].F = O;
                    break;
                case 'A':
                    bp[i].F = A;
                    break;
                case 'B':
                    bp[i].F = B;
                    break;
                default:
                    break;
                } 
            }
            bp[i].S = (int)(p[i].back() == '+');
        }
        vec<int> ansS;
        vec<int> ansP;

        if (p[2] == "?")
        {
            ansS = shojo[bp[0].F][bp[1].F];
            ansP = pos[1 - bp[0].S][1 -bp[1].S];
            cout << "Case " << caseN++ << ": " << p[0] << " " << p[1] << " ";
            printit(ansS, ansP);
            cout << endl;
        }
        else{
            int id = (p[0] == "?" ? 1 : 0);
            for (int i = 0; i < 4; i++){
                bool found = false;
                for (int &e : shojo[bp[id].F][i])
                {
                    if(e == bp[2].F){
                        found = true;
                        break;
                    }
                }
                if(found)
                    ansS.eb(i);
            }
            if(bp[id].S == 0 && bp[2].S == 1)
                ansP = {1};
            else
                ansP = {0, 1};
            cout << "Case " << caseN++ << ": ";
            if(id == 0){
                cout << p[0] << " ";
                printit(ansS, ansP);
                cout << " " << p[2];
            }
            else{
                printit(ansS, ansP);
                cout << " " << p[1] << " " << p[2];
            }
            cout << endl;
        }
    }
    return 0;
}