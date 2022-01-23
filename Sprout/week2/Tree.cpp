#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
	// initialize
	Node(int data=0): _data(data){
		_child.clear();
	}
	// print the data
	void printData() const {
		cout << _data << " ";
	}
	
	// they should better be private
	int           _data;
	vector<Node*> _child;
};

void dfs(Node* node){
	node->printData();
	for(int i=0; i<node->_child.size(); ++i)
		dfs(node->_child[i]);
}

void bfs(Node* root){
	queue<Node*> queue;
	while(!queue.empty()) queue.pop();
	queue.push(root);

	while(!queue.empty()){
		Node* tmp = queue.front();
		queue.pop();
		tmp->printData();
		for(int i=0; i<tmp->_child.size(); ++i)
			queue.push(tmp->_child[i]);
	}
}

int main(){
	Node *root, *node2, *node3, *node4, *node5, *node6;

	//  build the tree
	root = new Node(1);
	node2 = new Node(2);
	node3 = new Node(3);
	node4 = new Node(4);
	node5 = new Node(5);
	node6 = new Node(6);
	
	root->_child.push_back(node2);
	root->_child.push_back(node3);
	node2->_child.push_back(node4);
	node2->_child.push_back(node5);
	node3->_child.push_back(node6);
	
	// DFS
	cout << "DFS: ";
	dfs(root);
	cout << endl;

	// BFS
	cout << "BFS: ";
	bfs(root);
	cout << endl;
	
	return 0;
}

