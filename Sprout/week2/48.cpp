// AC 2019/11/25 17:01:12
#include <cstdio>
#include <iostream>
using namespace std;
class Node
{
public:
    int _data;
    Node *l_node;
    Node *r_node;
    Node *prenode;

public:
    Node(int a,Node * pa = NULL) : _data(a),l_node(pa),r_node(pa){};
    void addr(Node *pN)
    {
        this->r_node = pN;
    }
    void addl(Node *pN)
    {
        this->l_node = pN;
    }
};
void dfs_back(Node *N)
{
    if (N->l_node != NULL)
        dfs_back(N->l_node);
    if (N->r_node != NULL)
        dfs_back(N->r_node);
    cout << N->_data << endl;
    
}
void getnerate(Node *root)
{
    int Num;
    
    if (cin >> Num)
    {
        Node * pN = new Node(Num);
        Node * tmp = root;
       while(true){
           if(pN->_data > tmp->_data){
               if(tmp->r_node!=NULL)
                    tmp = tmp->r_node;
                else{
                    tmp->r_node = pN;
                    break;
                }
           }else{
                if(tmp->l_node!=NULL)
                    tmp = tmp->l_node;
                else{
                    tmp->l_node = pN;
                    break;
                }
           }
       }
        getnerate(root);
    }
}
int main()
{
    int Num;
    int root_N;
    cin >> root_N;
    Node *root = new Node(root_N);
    getnerate(root);
    dfs_back(root);
    return 0;
}