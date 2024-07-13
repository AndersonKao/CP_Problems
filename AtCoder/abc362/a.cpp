#include <bits/stdc++.h>
using namespace std;

int main(){
  string str;
  int a, b, c;
  cin >> a >> b >> c;
  cin >> str;
  if(str == "Red"){
    cout << min(b, c);
  } else if (str == "Blue"){
    cout << min (a, b);
  }
    else
      cout << min(a, c);
  return 0;
  }
