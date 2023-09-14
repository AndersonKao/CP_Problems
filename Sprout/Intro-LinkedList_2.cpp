#include <iostream>
using namespace std;
 // exist tail insert to tail
struct Node {
    int data;
    Node* next;
};

void printList(Node * address){
	cout << "Printing List: ";
	Node * ptr = address;
	while(ptr != NULL){
		cout << ptr->data << ' ';
		ptr = ptr->next;
	}
	cout << endl;
}
int main() {
    Node *head = NULL, *tail = NULL;
	int InsertData;
	while(cin >> InsertData){
		Node * newNode = new Node;
		newNode->data = InsertData;
		newNode->next = NULL;
		if(head == NULL){
			cout << "Head init\n";
			head = newNode;
            tail = head;
		}else{
			cout << "Now Tail: " << tail->data << endl;
			
			tail->next = newNode;
            tail = tail->next; 
            //a.k.a tail = newNode;
		}
		printList(head);
	}
	return 0;
}