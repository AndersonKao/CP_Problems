#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
string SSS[6] = {"AB", "AC", "BA", "BC", "CA", "CB"};
int length;
string Oristr;
vector<string> V;
void constr(int length)
{
    // vector<string> V;
    for (int i = 0; i < 6; i++)
    {
        string str = SSS[i];
        for (int i = 2; i <= length; i++)
        {
            if (str[i - 1] == 'A' && str[i - 2] == 'B')
            {
                str += "C";
            }
            else if (str[i - 1] == 'A' && str[i - 2] == 'C')
            {
                str += "B";
            }
            else if (str[i - 1] == 'C' && str[i - 2] == 'B')
            {
                str += "A";
            }
            else if (str[i - 1] == 'C' && str[i - 2] == 'A')
            {
                str += "B";
            }
            else if (str[i - 1] == 'B' && str[i - 2] == 'A')
            {
                str += "C";
            }
            else if (str[i - 1] == 'B' && str[i - 2] == 'C')
            {
                str += "A";
            }
        }
        V.push_back(str);
    }
    // return V;
}
int solv()
{
    string str;
    int ans = 2000000;
    for (int i = 0; i < 6; i++)
    {
        str = V[i];
        int counterr = 0;
        for (int i = 0; i < length; i++)
        {
            if (str[i] != Oristr[i])
                counterr++;
        }
        ans = min(ans, counterr);
    }
    return ans;
}
int main()
{
    cin >> length;
    cin >> Oristr;
    constr(length);

    int ANS = solv();
    cout << ANS << endl;
    return 0;
}