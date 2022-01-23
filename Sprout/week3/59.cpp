// AC 2019/12/14 12:01:38
#include <iostream>
#include <cstdio>
using namespace std;
int seq[1000005];
void Swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
int main()
{
    int T, action, tmp = 1, tmp_2;
    cin >> T;
    while (T--)
    {
        cin >> action;

        switch (action)
        {
        case 1:
            int target;
            scanf("%d", &target);
            seq[tmp] = target;
            tmp_2 = tmp;
            while (tmp_2 > 1 && seq[tmp_2] < seq[tmp_2 / 2])
            {
                // cout << "chage p:" << tmp_2 << "val:"<< seq[tmp_2] << "to p:" << tmp_2/2 << "val" << seq[tmp_2/2] << endl;
                Swap(&seq[tmp_2], &seq[tmp_2 / 2]);
                tmp_2 = tmp_2 / 2;
            }
            tmp++;
            break;
        case 2:
            if (tmp == 1)
            {
                printf("empty!\n");
                break;
            }
            printf("%d\n", seq[1]);
            tmp--;
            seq[1] = seq[tmp];

            tmp_2 = 1;
            while (1)
            {
                if (tmp_2 * 2 < tmp)
                {
                    bool r2 = false, r2_1 = false;
                    if (seq[tmp_2] > seq[tmp_2 * 2])
                    {
                        r2 = true;
                    }
                    if (seq[tmp_2] > seq[tmp_2 * 2 + 1])
                    {
                        r2_1 = true;
                    }
                    if (r2 && r2_1)
                    {
                        if (seq[tmp_2 * 2] < seq[tmp_2 * 2 + 1])
                        {
                            Swap(&seq[tmp_2], &seq[tmp_2 * 2]);
                            tmp_2 = tmp_2 * 2;
                            continue;
                        }
                        else
                        {
                            Swap(&seq[tmp_2], &seq[tmp_2 * 2 + 1]);
                            tmp_2 = tmp_2 * 2 + 1;
                            continue;
                        }
                    }
                    else if (r2)
                    {
                        Swap(&seq[tmp_2], &seq[tmp_2 * 2]);
                        tmp_2 = tmp_2 * 2;
                        continue;
                    }
                    else if (r2_1)
                    {
                        Swap(&seq[tmp_2], &seq[tmp_2 * 2 + 1]);
                        tmp_2 = tmp_2 * 2 + 1;
                        continue;
                    }
                }
                break;
            }
            break;
        }

        // for (int i = 0; i <= tmp; i++)
        // {
        //     cout << seq[i] << " ";
        // }
        // cout << endl;
    }
    return 0;
}