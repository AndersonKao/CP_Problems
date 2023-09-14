#include <iostream>
using namespace std;
 // no tail insert to tail
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
	Node* head;
    head = nullptr;
	int InsertData;
	while(cin >> InsertData){
		// Node initial
		Node * newNode = new Node;
		newNode->data = InsertData;
		newNode->next = nullptr;

		if(head == nullptr){
			cout << "Headed\n";
			head = newNode;
		}else{
			Node * ptr = head;
			while(ptr->next != nullptr){
				cout << "Going to next\n";
				ptr = ptr->next;
			}
			ptr->next = newNode;
		}
		printList(head);
	}
	return 0;
}