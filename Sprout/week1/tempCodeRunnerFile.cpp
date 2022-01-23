#include <stdio.h>
#include <iostream>
struct Node
{
    int _data;
    Node *_next;
    Node *_pre;
};
int main()
{
    int N, T, act, tar;
    scanf("%d", &N);
    Node **arr = (Node **)malloc(sizeof(Node *) * (N + 2));
    Node *tmp = NULL, *start;
    for (int i = 0; i < N; i++)
    {
        Node *car = new Node;
        car->_data = i + 1;
        arr[i + 1] = car;
        car->_pre = tmp;
        car->_next = NULL;
        if (i != 0)
            tmp->_next = car;
        else // first element
            start = car;
        tmp = car;
    }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &act, &tar);
        if (act == 0)
        {
            Node *tmp1, *tmp2;
            if (arr[tar] == start) // fisrt one
            {
                tmp2 = arr[tar]->_next;
                tmp2->_pre = NULL;
                start = tmp2;
            }
            else if (arr[tar]->_next == NULL) // last one
            {
                tmp1 = arr[tar]->_pre;
                tmp1->_next = NULL;
            }
            else
            {
                tmp1 = arr[tar]->_pre;
                tmp2 = arr[tar]->_next;
                tmp1->_next = tmp2;
                tmp2->_pre = tmp1;
            }
        }
        else
        {
            if (start == arr[tar]) // first one can't move anymore
                continue;
            Node *tmp3 = arr[tar]->_pre;
            if (start == tmp3)
            {
                start = arr[tar];
                arr[tar]->_next->_pre = tmp3;
                tmp3->_next = arr[tar]->_next;
                arr[tar]->_pre = NULL;
                arr[tar]->_next = tmp3;
            }
            else
            {
                Node *tmp4 = arr[tar]->_pre->_pre;
                tmp4->_next = arr[tar];
                if (arr[tar]->_next != NULL)
                    arr[tar]->_next->_pre = tmp3;
                tmp3->_next = arr[tar]->_next;
                arr[tar]->_pre = tmp3->_pre;
                arr[tar]->_next = tmp3;
                tmp3->_pre = arr[tar];
            }
        }
        Node *tmp2 = start;
        while (tmp2->_next != NULL)
        {
            printf("%d ", tmp2->_data);
            tmp2 = tmp2->_next;
        }
        printf("%d", tmp2->_data);
    }

    return 0;
}