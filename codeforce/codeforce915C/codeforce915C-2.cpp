#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int anum[10] = {0};
    int along;
    string bnum;
    char num;

    for(along = 0;; along++)
    {
        cin.get(num);
        if(num == '\n')
            break;
        anum[num - 48]++;
//        cout << "kkk" << endl;
    }//cout << along;
//    for(int i = 0; i < 10; i++)
//    {
//        cout << anum[i] < " ";
//    }
//    cout << endl;
    cin >> bnum;
    int rivisiona[along] = {0};
    int blong = bnum.length();
    bool flagtex = true;
    if(blong > along)
        flagtex = false;

    bool pullflag = true;
    int writingnum;
    int aliningtex = 0;
    while(flagtex)
    {
        writingnum = bnum[aliningtex] -48;
        if(anum[writingnum] == 0)
        {
            for(int i = writingnum-1; i >=0; i--)
            {
                if(anum[i]>0)
                {
                    anum[i]--;
                    rivisiona[aliningtex] = i;
                    flagtex = false;
                    break;
                }

            }
        }else
        {
                anum[writingnum]--;
                rivisiona[aliningtex] = writingnum;
        }
        //if((rivisiona[aliningtex]-48) < (bnum[aliningtex]-48))

        aliningtex++;
        if(aliningtex > along)
            flagtex = false;
    }
//    for(int i = 0; i < along; i++)
//        {
//            cout << rivisiona[i] ;
//        }
//        cout << endl;

        int ddex = 9;
        for(int i = aliningtex; i < along; i++)
        {
            if(anum[ddex] != 0)
            {
                rivisiona[i] = ddex;
                anum[ddex]--;
            }else
            {
                ddex--;
                i--;
            }
        }

    for(int i = 0; i < along; i++)
        {
            cout << rivisiona[i] ;
        }
        cout << endl;
        return 0;
    return 0;
}
