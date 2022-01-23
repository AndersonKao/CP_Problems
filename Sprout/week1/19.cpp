// AC 2019/11/20 17:19:44
// Is there any better solution?
#include <cstdio>
#include <iostream>
#include <string>
#define endl '\n'
using namespace std;
struct Node
{
    int _data;
    Node *_pre;
};
struct Steck
{
    Node *head = NULL;
    int elenum = 0;
};
bool isItEmpty(Steck *N);
int pop(Steck *);
void push(Steck *, int num);
int main()
{
    int T, seqlen, num, targer;
    
    cin >> T;
    while (T--)
    {
        Steck slk, tmp, tmp_2, final;
        cin >> seqlen;
        for (int i = seqlen; i > 0; i--)
        {
            push(&slk, i);
        }
        for (int i = 0; i < seqlen; i++)
        {
            cin >> targer;
            int tmpnum = -1;
            if (!isItEmpty(&tmp))
            {
                tmpnum = pop(&tmp);
                if (tmpnum != targer)
                    push(&tmp, tmpnum);
                else
                {
                    //cout << "find" << tmpnum << "!!\n";
                    push(&final, tmpnum);
                    continue;
                }
            }
            while (!isItEmpty(&slk))
            {
                tmpnum = pop(&slk);
                if (tmpnum != targer)
                    push(&tmp, tmpnum);
                else
                {
                    //cout << "find" << tmpnum << "!!\n";
                    push(&final, tmpnum);
                    break;
                }
            }
        }
        if (final.elenum == seqlen)
        {
            cout << "Yes\n";
        }
        else{
            cout << "No\n";
        }

        // switch(action){
        //     case 1:
        //         cin >> num;
        //         push(&slk,num);
        //         break;
        //     case 2:
        //         cout << pop(&slk) << endl;
        //         break;
        // }
    }
    return 0;
}
int pop(Steck *N)
{
    if (N->elenum)
    {

        int ans = N->head->_data;
        Node *tofree = N->head;
        N->head = N->head->_pre;
        N->elenum--;
        delete(tofree);
        return ans;
    }
    else
    {
        printf("empty\n");
        return -1;
    }
}
void push(Steck *N, int num)
{
    N->elenum++;
    Node *another = new Node;
    another->_data = num;
    another->_pre = N->head;
    N->head = another;
}
bool isItEmpty(Steck *N)
{
    if (N->elenum == 0)
        return true;
    return false;
}