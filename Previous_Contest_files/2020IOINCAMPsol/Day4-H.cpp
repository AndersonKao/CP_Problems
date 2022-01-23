#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
map<long long, int> M;
int main()
{
    int N;
    cin >> N;
    int data;
    for (int i = 0; i < N; i++)
    {
        cin >> data;
        M[data]++;
    }
    int ANSNum = 0;
    for (auto it : M)
    {
        // cout << "Visiting " << it.first << " are " << it.second << "(s)" << endl;
        if (it.second > ANSNum)
        {
            ANSNum = it.second;
        }
    }
    vector<long long> ANS;
    for (auto it : M)
    {
        if (it.second == ANSNum)
        {
            ANS.push_back(it.first);
        }
    }
    sort(ANS.begin(), ANS.end());
    for (int i = 0; i < ANS.size(); i++)
    {
        cout << ANS[i] << (i == ANS.size() - 1 ? '\n' : ' ');
    }
    return 0;
}