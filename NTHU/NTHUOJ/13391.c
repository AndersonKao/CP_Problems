#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    struct Node* next, *prev; 
};
typedef struct Node Node;

Node* head = NULL, *tail = NULL;

Node* mallocNode(int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = val;
    newNode->next  = newNode->prev = NULL;
    return newNode;
}

void AddFront(int val){
    Node* newNode = mallocNode(val);
    if(head)
    {
        newNode->next = head;
        head->prev = newNode;
    }
    else
        tail = newNode;
    head = newNode;
}
void delete(int val){
    Node *tode;
    Node*ptr = head;
    while(ptr)
    {
        tode = NULL;
        if(ptr->value == val)
        {
            if(ptr->prev)
                ptr->prev->next = ptr->next;
            if(ptr->next)
                ptr->next->prev = ptr->prev;
            tode = ptr;
        }
        ptr = ptr->next;
        if(tode)
        {
            if(head == tode)
                head = head->next;
            if(tail == tode)
                tail = tail->prev;
            free(tode);
        }
    }
}
void AddBack(int val){
    Node* newNode = mallocNode(val);
    if(tail)
    {
        newNode->prev = tail;
        tail->next = newNode;
    }
    else
        head = newNode;
    tail = newNode;
}

int main(){
    char op[10];
    int target;
    while(~scanf("%s", op)){
        scanf("%d", &target);
       // printf("Operation %s : %d\n", op, target);
        switch (op[3])
        {
        case 'F':
            /* code */
            AddFront(target);
            break;
        case 'B':
            AddBack(target);
            break;
        case 'e':
            delete(target);
            break;
        default:
            break;
        }
        /*
        Node * ptr = head;
        while(ptr)
        {
            printf("%d%c", ptr->value, (ptr->next ? ' ' : '\n'));
            ptr = ptr->next;
        }
        */

    }
    while(head)
    {
        printf("%d%c", head->value, (head->next ? ' ' : '\n'));
        head = head->next;
    }

    return 0;
}