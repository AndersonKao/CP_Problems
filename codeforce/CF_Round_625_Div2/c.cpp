#include <iostream>
#include <cmath>
using namespace std;
class database;
class database{
    public:
        int beauty;
        int howlong;
};
database beau[200005];
int Ans = 0;
int main(){
    int N;
    cin >> N;
    database * head = new database;
    database* tmp = 0;
    for(int i = 0;i<N;i++){
        
        cin >> beau[i].beauty;
        beau[i].howlong = 1;
    }
    if(N == 1)
        cout << beau[0].beauty << "\n";
    else{
        int index;
        bool flag = true;
        while(flag){
            index = 0;
            while(index < N)
                   if((abs(beau[index].beauty - beau[index + beau[index].howlong].beauty) == beau[index].howlong){
                    beau[i].beauty += beau[index + beau[index].howlong].beauty;
                    beau[i+1] = 0;
                }
                index += beau[i].howlong;
            }
        }
        }   
    }
    return 0;
}