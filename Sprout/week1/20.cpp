// AC 2019/11/21 17:40:03
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;
int whiTeam[1000000] = {0};
int main()
{
    int chinum, Cases = 0, N, nums, n; //
    char action[10];
    while (~scanf("%d",&chinum))
    {
        for (int i = 0; i < 1000000; i++)
            whiTeam[i] = 0;
        printf("Line #%d\n", ++Cases);
        queue<int> Line;            // 紀錄隊伍裡的順序
        queue<int> evertTeam[1050]; // 紀錄各組的人順序
        for (int i = 1; i <= chinum; i++)
        {
            scanf("%d",&nums);
            while(nums--){
                scanf("%d",&n);
                whiTeam[n] = i;
            }
        }
        while (cin >> action)
        {
            if (action[0] == 'S')
                break;
            switch (action[0])
            {
            case 'D':
            {
                int T = Line.front();
                printf("%d\n",evertTeam[T].front());
                evertTeam[T].pop();
                if (!T || evertTeam[T].empty())
                    Line.pop();
                break;
            }
            case 'E':
            {
                scanf("%d",&N);
                if(!whiTeam[N]){
                    Line.push(0);
                } 
                else if(evertTeam[whiTeam[N]].empty())
                    Line.push(whiTeam[N]);
                evertTeam[whiTeam[N]].push(N);
                break;
            }
            default:
                break;
            }
        }
    }
    return 0;
}