#include <iostream>
#include <string>
using namespace std;
struct Node{
    char ch;
    Node * next, * prev;
    Node(char ch): ch(ch), lc(0), rc(0){}

}
int main(){
    int Len, Q;
    string str;
    cin >> Len >> Q;
    cin >> str;
    Node * head = new Node(str[0]);
    Node * ptr;
    for(int i = 1; i < Len; i++){
        Node * newNode = new Node(str[1]);
        ptr->next = newNode;
        newNode->prev = ptr;
        ptr = ptr->next;
    }
    int L, R;
    while(Q--){
        cin >> L >> R;
        
    }
    return 0;
}