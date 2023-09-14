struct node{
    int data;
    node *prev, *next;
};
void insert(node* prev, int data){
    node * newNode = new node;
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    
    newNode->prev = prev;
    if(prev != nullptr)
        newNode->next = prev->next;
    if(prev != nullptr){
        if(prev->next != nullptr)
            (prev->next)->prev = newNode;
        prev->next = newNode;
    }
}
void remove(node *ptr){
    node *prevNode = ptr->prev;
    node *nextNode = ptr->next;
    if(prevNode != nullptr)
        prevNode->next = nextNode;
    
    if(nextNode != nullptr)
        nextNode->prev = prevNode;
    delete ptr;
}