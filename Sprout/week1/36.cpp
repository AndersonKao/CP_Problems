// AC 2019/11/18 19:37:15
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
struct Node{
    int _data;
    Node* _pre;
};
int main(){
    int T,action,num;
    Node* head = NULL;
    cin >> T;
    while(T--){
        cin >> action;
        switch(action){
            case 1:
            {
                cin >> num;
                Node *another = new Node;
                another->_data = num;
                another->_pre = head;
                head = another;
                break;
            }
            case 2:
                if(head == NULL)
                    printf("empty!\n");
                else{
                    printf("%d\n",head->_data);
                    head = head->_pre;
                }
                break;
        }
        //printf("%p\n", head);
    }
    return 0;
}
