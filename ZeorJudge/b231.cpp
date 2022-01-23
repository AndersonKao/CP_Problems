// AC 2020-02-06 16:07
#include <iostream>
#include <queue>
#include <climits>
using namespace std;
typedef struct{
    int printtime;
    int edittime;
}Node;

Node seq[1005];
class Compare{
    public:
        bool operator() (const Node &lhs, const Node &rhs){
            if(lhs.edittime == rhs.edittime){
                return lhs.printtime < rhs.printtime;
            }
            return lhs.edittime < rhs.edittime;
        }
};



int ANS;

int main(){
    int Num; 
    while(cin >> Num){
        priority_queue<Node,vector<Node>,Compare> q;
        ANS = 0;

        for(int i = 0;i<Num;i++){
            Node tmp;
            cin >> tmp.printtime >> tmp.edittime;
            q.push(tmp);
            ANS += tmp.printtime;
        }
        int remainedit = 0;
        while(!q.empty()){
            Node tmp2;
            tmp2 = q.top();
            
            remainedit -= tmp2.printtime;
            remainedit = remainedit > tmp2.edittime ? remainedit : tmp2.edittime;
            
            // cout << tmp2.printtime << " " << tmp2.edittime <<endl;
            // cout << "ANS: " << ANS << endl;
            q.pop();        
        }
        // cout << "remain" << remainedit << endl;
        ANS = ANS + remainedit;
        cout << ANS << endl;

    }

    return 0;
}