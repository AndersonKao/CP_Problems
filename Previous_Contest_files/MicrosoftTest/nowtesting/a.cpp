#include <iostream>
#include <cmath>
using namespace std;
char ansstr[4][100] = {"Not triangle\n","Right triangle\n"
,"Obtuse triangle\n", "Acute triangle\n"};
typedef struct{
    long long v1;
    long long v2;
    double length;
}vectors;

void countlen(vectors &a){
    a.length = sqrt(a.v1*a.v1 + a.v2 * a.v2);
}

double innerproduct(vectors a, vectors b){
    return a.v1 * b.v1 + a.v2 * b.v2;
}
int main(){

    long long x[3],y[3];
    for(int i=0;i<3;i++){
        cin >> x[i] >> y[i];
    }
    vectors q1,q2;
    double min = 10;
    // cout << "testing" << endl;
    for(int i=0;i<3;i++){
        
        int j = (i == 2 ? 0 : i+1);
        int k = (i == 0 ? 2 : i-1);
        q1.v1 = x[j] - x[i];
        q1.v2 = y[j] - y[i];
        q2.v1 = x[k] - x[i];
        q2.v2 = y[k] - y[i];
        countlen(q1);
        countlen(q2);
        double now = innerproduct(q1,q2) / q1.length / q2.length;
        min = min < now ? min : now;
        // cout << min << endl;
    }
    
    if ( min > 0.99999 || min < -0.99999){
        cout << "Not triangle\n";
    }else if(min < 0 && min > -1.0){
        cout << "Obtuse triangle\n";
    }else if(min == 0){
        cout << "Right triangle\n";
    }else if(min > 0 && min < 1){
        cout << "Acute triangle\n";
    }else{
        cout << "Not triangle\n";
    }

    return 0;
}