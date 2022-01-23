#include <iostream>
using namespace std;

int main() {
   int iii;
   cin >> iii;
   if(iii == 0)
       {
           cout << 1 << endl << 0 << endl;
           return 0;
       }
   int deposit[iii][100];
   int line[iii] = {-1};
   for (int i=0;i<iii;i++)
   {
       //line[i] = -1;
       for(int k=0;k<100;k++)
           deposit[i][k] = 0;
   }

    int u,m;
    for(int i = 0 ; i < iii;i++)
    {
     cin >> u;
     deposit[i][1] = u;
     if(u == 0)
     line[i] = 0;
     for(int k = 1; k <= u;k++)
     {
     cin.get();
      cin >> m;
      deposit[i][k+1] = m;
     deposit[m-1][0] = 1;
     }
    }
    for(int i = 0;i<iii;i++)
    {
        for(int k = 0;k<iii;k++)
          cout << deposit[i][k] << " ";
    cout << endl;
    }

    int rootpoint;
    for(int i = 0;i<iii;i++)
    {
        if(deposit[i][0] == 0)
        {
            rootpoint = i+1;
            break;
        }
    }
    cout << rootpoint;

    bool flag = true;
    bool numtest;
    int num,tonum;
    while(flag)
    {
        for(int i = 0;i<iii;i++)
        {
            if(line[i]==-1)
            {

                tonum = 0;
                numtest = true;
                for(int n = 0;n<deposit[i][1];n++)
                {
                   num = line[deposit[i][n+2]-1];
                   if(num == -1)
                     {
                         numtest = false;
                         break;
                     }

                    tonum+=num;
                }
            if(numtest)
            line[i] = tonum+1;
            }
        }

        for(int i = 0;i<iii;i++)
        {
            if(line[i] == -1)
             {
                 flag =true;
                 break;
             }else if(i == iii-1)
             {
                 flag = false;
                 break;
             }
        }
    }
    int total = 0;
    for(int i =0;i<iii;i++)
       total+=line[i];
    cout << endl << total-1;
    return 0;
}
