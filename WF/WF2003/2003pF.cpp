// AC
// UTC+0 2022-05-14 09:03:10
#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n;i++)
#define REP1(i, n) for (int i = 1; i <= (int)n;i++)
#define debug(x) //cout << #x << " > " << x << endl;
template <typename T>
using vec = vector<T>;

vec<string> table2 = {
    "0000",
    "0001",
    "0010",
    "0011",
    "0100",
    "0101",
    "0110",
    "0111",
    "1000",
    "1001",
    "1010",
    "1011",
    "1100",
    "1101",
    "1110",
    "1111",
};
vec<string> table = {
    "0", "1", "2", "3",
    "4", "5", "6", "7",
    "8", "9", "A", "B",
    "C", "D", "E", "F",

};
string strA, strB;
string decode2(string A){
    string res;
    REP(i, A.length())
        if(isdigit(A[i]))
            res += table2[(A[i] - '0')];
        else
            res += table2[(A[i] - 'A' + 10)];
    return res;
}
string encode(string A){
    string res;
    int i = 0;
   // cout << A.length() << " len\n";
    while (i < (int)A.length())
    {
        int idx = 0;
        for (int j = 0; j < 4; j++, i++)
        {
            if(A[i] == '1')
                idx += 1;
            if(j < 3)
                idx <<= 1;
        }
        debug(idx);
        res += table[idx];
    }
    return res;
}
void subroutine(string& res, string& str, int& pt){
    int a = str[pt] - '0';
    //cout << pt << ", ";
    if (a == 1)
    {
        res += str[pt];
        res += str[pt + 1];
        pt += 2;
    }
    else{
        res += str[pt];
        pt += 1;
        subroutine(res, str, pt);
        subroutine(res, str, pt);
        subroutine(res, str, pt);
        subroutine(res, str, pt);
    }
}
string getappend(string & str, int& pt){
    string res;
    //cout << "strlen= " << str.length() << endl;
    //cout << "at " << str << " position = " << pt << endl;
    subroutine(res, str, pt);
    //cout << "subroutine: " << res << endl;
    //cout << endl;
    return res;
}

void process(string& ANS, int& ptA, int& ptB){
    int a = strA[ptA] - '0', b = strB[ptB] - '0';
    int a2 = strA[ptA + 1] - '0', b2 = strB[ptB + 1] - '0';
    /*
    cout << ptA << ", " << ptB << endl;
    cout << "A: " << a << a2 << endl;
    cout << "B: " << b << b2 << endl;
    */
    if (a == 1)
    {
        if(b == 1){
            if(a2 == 1 && b2 == 1)
                ANS += "11";
            else
                ANS += "10";
            ptA += 2, ptB += 2;
        }
        else{
            if(a2 == 1){
                string tail = getappend(strB, ptB);
                ANS += tail;
            }
            else
            {
                string tail = getappend(strB, ptB);
                ANS += "10";
            }
            ptA += 2;
        }
    }
    else {
        if(b == 1){
            if(b2 == 1){
                string tail = getappend(strA, ptA);
                ANS += tail;
            }
            else
            {
                string tail = getappend(strA, ptA);
                ANS += "10";
            }
            ptB += 2;
        }
        else{
            ptA++, ptB++;
            ANS += "0";
            process(ANS, ptA, ptB);
            process(ANS, ptA, ptB);
            process(ANS, ptA, ptB);
            process(ANS, ptA, ptB);
        }
    }
    debug(ANS);
}
pair<string, bool> eliminate(string &str, int& pt){
    string res = "";
    bool contains = false;
    int a = str[pt] - '0';
    if(a == 1){
        contains = str[pt + 1] == '1';
        res = str[pt];
        res += str[pt + 1];
        pt += 2;
    }
    else{
        pt++;
        REP(i, 4){
            pair<string, bool> eps = eliminate(str, pt);
            contains = contains || eps.second;

            res += eps.first;
        }
        if(contains == false)
            res = "10";
        else
            res = "0" + res;
    }
    return {res, contains};
}
string processANS(string ANS)
{
    int pt = 0;
    return eliminate(ANS, pt).first;
}
int main()
{
    int cnt = 1;
    while (cin >> strA >> strB)
    {
        if(strA == "0" && strB == "0")
            break;
        strA = decode2(strA);
        strB = decode2(strB);

        debug(strA);
        debug(strB);
        int stptA, stptB;
        REP(i, strA.length())
            if(strA[i] == '1') {
                stptA = i + 1;
                break;
            }
        REP(i, strB.length())
            if(strB[i] == '1') {
                stptB = i + 1;
                break;
            }
        string ANS;
        process(ANS, stptA, stptB);
        debug(ANS);
        ANS = processANS(ANS);
        debug(ANS);
        ANS = "1" + ANS;
        string head = "";
        int limit = (4 - (ANS.length() % 4)) %4;
        for (int i = 0; i < limit; i++)
        {
            head += "0";
        }
        ANS = head + ANS;
        ANS = encode(ANS);
        debug(ANS);
        if(cnt > 1)
            cout << endl;
        cout << "Image " << cnt++ << ":" << endl;
        cout << ANS << endl;
    }
    return 0;
}
