#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        char s[100005], t[100005];
        scanf("%s %s", s, t);
        int slength = strlen(s), tlength = strlen(t);
        bool table[500] = {0};
        int charnum[500] = {0};
        int charfirst[500] = {-1};
        for (int i = 0; i < slength; i++)
        {
            table[(int)s[i]] = true;
            charnum[s[i]]++;
            if(charfirst[(int)s[i]] == -1)
                charfirst[(int)s[i]] = i;
        }
        bool flag = false;
        for (int i = 0; i < tlength; i++)
        {
            if (table[(int)t[i]] == false)
            {
                printf("-1\n");
                flag = true;
                break;
            }
        }
        if (flag)
        {
            continue;
        }
        int index = 0, ans = 0;
        while (index < tlength)
        {
            int charused[500] = {0};
            for (int tmpindex = charfirst[t[index]]; tmpindex <slength; tmpindex++)
            {
                charused[s[tmpindex]]++;
                if (s[tmpindex] == t[index])
                {
                    index++;
                }
                if(charused[t[index]]>= charnum[t[index]])
                {
                    break;
                }    
            }
            ans++;
        }

        printf("%d\n", ans);

    }

return 0;
}