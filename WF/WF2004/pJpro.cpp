#include <iostream>
using namespace std;

int main(){

    int NP, NC;
    while( cin >> NP >> NC ){
        cout << NP << " " << NC << endl;
        if (NP == 0 && NC == 0)
            break;
        for (int i = 0; i < NP; i++)
        {
            double a, b;
            cin >> a >> b;
            cout << a << " " << b << endl;
        }
        for (int i = 0; i < NC; i++){
            int a;
            cin >> a;
            cout << a << " ";
            for (int j = 0; j < 4;j++){
                double b;
                cin >> b;
                cout << b << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}