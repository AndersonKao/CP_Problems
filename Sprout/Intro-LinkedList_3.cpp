#include <iostream>
using namespace std;
 // Total Demonstration
struct Node {
    int data;
    Node* next;
};
void printList(Node *address);
void insertData(Node **headAdd, Node **tailAdd, int toInsertData);
void deleteData(Node ** head, Node** tail, int toDeleteData);

int main() {
    Node *head = NULL, *tail = NULL;
    string Option;
    while(cin >> Option){
        if(Option == "Insert"){
            int toInsertData;
            cin >> toInsertData;
            insertData(&head, &tail, toInsertData);
        }else if(Option == "Delete"){
            int toDeleteData;
            cin >> toDeleteData;
            deleteData(&head, &tail, toDeleteData);
        }
        printList(head);
    }
	
	return 0;
}
void printList(Node * address){
	cout << "Printing List: ";
	Node * ptr = address;
	while(ptr != NULL){
		cout << ptr->data << ' ';
		ptr = ptr->next;
	}
	cout << endl;
}
void insertData(Node **headAdd, Node **tailAdd, int toInsertData){
    Node * newNode = new Node;
    newNode->data = toInsertData;
    newNode->next = NULL;
    // *headadd = head
		if(*headAdd == NULL){ // 如果 List本來就是空的
            cout << "First Node\n";
			(*headAdd) = newNode;
            (*tailAdd) = (*headAdd);// initialize tail *tailAdd = newNode
		}else{ // 直接從tail加入
            cout << "Now Tail: " << (*tailAdd)->data << endl;
			(*tailAdd)->next = newNode;
            (*tailAdd) = (*tailAdd)->next; 
            //a.k.a tail = newNode;
		}
	
}
void deleteData(Node ** head, Node** tail, int toDeleteData){
    Node * ptr = *head;
    Node * prev = NULL;
    if(ptr == NULL){
        cout << "No Data in the List!!\n";
        return; // important
    }
    else{
        if(ptr->data == toDeleteData){ // 如果head馬上就是找到的Data
            *head = (*head)->next;
            Node * toDelete = ptr;
            delete toDelete;
        }else{
            while(ptr != NULL && ptr->data != toDeleteData){// 用ptr遍歷整個List
                prev = ptr;
                ptr = ptr->next;
            }
            if(ptr == NULL){ // ptr跑到NULL代表找不到這筆資料
                cout << "Can't find Data\n";
            }else{
                Node * toDelete = ptr;
                prev->next = ptr->next;
                if(prev->next == NULL){ // 代表ptr本來就是tail, 而 prev將會是新的tail
                    (*tail) = prev;
                }
                delete toDelete;
            }
        }
    }
}