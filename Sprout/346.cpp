// AC 2020/04/24 09:02:42
#include <iostream>
using namespace std;

int GCD(int a, int b){
    if(a == 0 && b == 0)
        return 0;
    if(a < b){
        int c = b;
        b = a;
        a = c;
    }

    bool a_is_even, b_is_even;
    if(a % 2 == 0)
        a_is_even = true;
    else
        a_is_even = false;

    if(b % 2 == 0)
        b_is_even = true;
    else
        b_is_even = false;
    if(b == 0){
        cout << "one zero" << endl;
        return a;
    }else if(a_is_even && b_is_even){
        cout << "both even" << endl;
        return 2 * GCD(a / 2, b / 2);
    }else if(!a_is_even && !b_is_even){
        cout << "both odd" << endl;
        return GCD(a - b, b);
    }else if(!a_is_even && b_is_even){
        cout << "one odd" << endl;
        return GCD(a,b / 2);
    }else if(a_is_even && !b_is_even){
        cout << "one odd" << endl;
        return GCD(a / 2, b);
    }
}


int main(){
    int a, b;
    cin >> a >> b;

    cout << GCD(a,b) << endl;

    return 0;
}