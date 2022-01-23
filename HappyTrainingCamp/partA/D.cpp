#include <bits/stdc++.h>
using namespace std;

string str;

double getvalue(char ch)
{
    switch (ch)
    {
    case 'C':
        return 12.01;
        break;
    case 'H':
        return 1.008;
        break;
    case 'O':
        return 16.00;
        break;
    case 'N':
        return 14.01;
        break;
    default:
        return 0.0;
        break;
    }
}

double solve()
{
    getline(cin, str);

//    cout << str << "\n";
    double ans = 0.0;

    unsigned index = 0;
    while(index < str.length())
    {
        if(isdigit(str[index+1])){
            unsigned mul = 0;
            double multiplier = getvalue(str[index]);
            index++;
            while(isdigit(str[index]))
            {
                mul *= 10;
                mul += str[index] - '0';
                index++;
            }
            ans += mul * multiplier;
        }
        else if(isalpha(str[index + 1]) || index+1 >= str.length())
        {
            ans += getvalue(str[index]);
            index++;
        }
        //cout << "ans: " << ans << endl;
    }
    

        return ans;
}

int main(){
    //cin.tie(0);
    //ios::sync_with_stdio(false);
    int T;
    cin >> T;
    getc(stdin);
    cout << fixed << setprecision(3);
    while(T--){
        cout << solve() << "\n";
    }
    return 0;
}