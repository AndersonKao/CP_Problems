// AC 2019/12/14 12:01:38
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
#define PARENT(x) ((x-1)/2)
#define LCHILD(x) (x*2 + 1)
#define RCHILD(x) (x*2 + 2)
void Swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}
class heap{
private:
    int* seq ;
    int size;

public:
    heap();
    ~heap();
    void push(int data);
    bool empty();
    int pop();
    void clear();
    void print();
};
heap::heap(){
    seq = new int[1000005];
    size = 0;
}
heap::~heap(){
    delete seq;
}
/*
            0
           / \
          1   2
         / \ / \
        3  4 5  6
*/
void heap::push(int data){
    this->seq[this->size] = data;
    int iter = this->size;
    while (iter > 0 && seq[iter] < seq[PARENT(iter)])   // seq[((x-1)/2)]
    {
        Swap(&seq[iter], &seq[PARENT(iter)]);
        iter = PARENT(iter);
    }
    this->size++;
}
bool heap::empty(){
    return this->size == 0;
}
int heap::pop(){
    int toreturn = this->seq[0];
    this->seq[0] = this->seq[size-1];
    size--;
    int iter = 0;
    int compare_index;
    while(true){
        if(RCHILD(iter) < size)
            compare_index = (seq[LCHILD(iter)] < seq[RCHILD(iter)] ? LCHILD(iter) : RCHILD(iter));
        else if(LCHILD(iter) < size)
            compare_index = LCHILD(iter);
        else
            // since there are no child
            break;
        if(seq[iter] > seq[compare_index]){
            Swap(&seq[iter], &seq[compare_index]);
            iter = compare_index;
        }else
            break;
    }

    return toreturn;
}

void heap::clear(){
    size = 0;
}

void heap::print(){
    for (int i = 0; i < size; i++)
        printf("%d ", seq[i]);
    printf("\n");
}
int main()
{
    int T, action;
    cin >> T;
    heap myheap;
    while (T--)
    {
        scanf("%d", &action);
        switch (action)
        {
        case 1:
            int target;
            scanf("%d", &target);
            myheap.push(target);
            break;
        case 2:
            if (myheap.empty())
                printf("empty!\n");
            else
                printf("%d\n", myheap.pop());
            break;
        }
    }
    return 0;
}