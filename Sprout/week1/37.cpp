// AC 2019/11/19 09:50:44 Is there any better solution?
// I think I use too much pointer
#include <iostream>
using namespace std;
struct Node
{
    int _data;
    Node *_next;
};
int main()
{
    int T;
    cin >> T;
    Node first;
    
    Node *head = &first;
    head->_next = NULL;
    Node *end = NULL;
    while (T--)
    {
        int action, num;
        cin >> action;
        switch (action)
        {
        case 1:
        {
            cin >> num;
            Node *another = new Node;
            another->_data = num;
            if(head->_next == NULL)
                head->_next = another;
            if(end == NULL)
                end = another;
            else
            {
                end->_next = another;
                end = another;
            }
            break;
        }
        case 2:
            if (head == end)
                printf("empty!\n");
            else{
                printf("%d\n",head->_next->_data);
                head = head->_next;
            }
            
            break;
        }
    }
    return 0;
}