#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <string>
#include <utility>
using namespace std;
struct Node{

    float sum;
    char ch;
    Node* L, *R;
    Node(Node* L, Node* R){
        this->sum = L->sum + R->sum;
        this->L = L;
        this->R = R;
    }
    Node(char ch, float ratio):ch(ch){
        L = R = nullptr;
        sum = ratio;
    }
};

Node* construct_huff(string& str){
     
    int len = str.length();
    map<char, int> ratio;
    for(int i = 0; i < len; i++){
        if(ratio.find(str[i]) == ratio.end())
           ratio[str[i]] = 1; 
        else
            ratio[str[i]]++;
    }
    priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<pair<double, Node*>>> Pq;
    for(std::map<char, int>::iterator it = ratio.begin(); it!=ratio.end(); ++it){
        double rate = (double)it->second / (double)len;
        Pq.emplace(rate, new Node(it->first, rate));
    }
    while(Pq.size() > 1){
        Node *first = Pq.top().second;
        Pq.pop();
        Node *second= Pq.top().second;
        Pq.pop();
        Pq.emplace(first->sum + second->sum, new Node(first, second));
    }

    return Pq.top().second;
}

void visit(Node* n, string str){
    if(n->L == nullptr && n->R == nullptr){
        cout << n->ch << " " << str << endl;
        return;
    }
    if(n->L){
        visit(n->L, str + "1");
    }
    if(n->R){
        visit(n->R, str + "0");
    }
}


void encode(Node* tree){
    cout << "encoding is ...\n";
    visit(tree, "");
}
void decode(Node* tree, string str){

    cout << "the string is ....\n";
    Node* ptr = tree;
    unsigned int len = str.length();
    for (int i = 0; i < len; i++){
        if(str[i] == '0'){
            if(ptr->R)
                ptr = ptr->R;
        }else if(str[i] == '1'){
            if(ptr->L)
                ptr = ptr->L;
        }
        if(ptr->L == nullptr && ptr->R == nullptr){
            cout << ptr->ch;
            ptr = tree;
        }
    }


    cout << "\n\n";
}



void test(){
    string str;
    cin >> str;
    Node *tree = construct_huff(str);

    encode(tree);
    while(cin >> str)
        decode(tree, str);
}

int main(){
    test();
    return 0;
}