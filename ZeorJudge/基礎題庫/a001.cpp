#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    std::string s;
    while (cin >> s)
    {
        cout << "hello, " <<  s << endl;
    }
    return 0;
}
