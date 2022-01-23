#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int l_b(int n, int *ar, int R_limit)
{
   int L = 0, R = R_limit ;
   int mid = (L + R) / 2;
   while (L < (R - 1))
   {
      //printf("L:%d  R:%d\n", L, R);
      mid = (L + R) / 2;
      if (ar[mid] > n)
      {
         R = mid;
      }else if (ar[mid] < n)
      {
         L = mid;
      }else if(ar[mid] == n)
          return mid;
   }
   return R;
}
int appear[500005];
int arr[500005],arr2[500005];
int main(){
    int T, n;
    map<int,int> numindex; 
    set<int> exist; // num which inputed
    cin >> T;
    int tmp = 0,index =0;
    while(T--){
        int n; cin >> n;

    }
    for(int i=0;i<T;i++)
    {
        cin >> arr[i];
        arr2[i] = arr[i];

    }
    sort(arr2, &arr2[T]);
  //  for(int i=0;i<T;i++)
    //    cout << arr2[i] << " ";

    for(int i=0;i<T;i++){
        int n = arr2[i];
        if(exist.count(n)){
          //  cout << "counted!\n";
            appear[numindex[n]]++;
        }else{
          //  cout << "yaI'll create one\n";
            exist.insert(n);
            numindex[n] = tmp++;
            appear[numindex[n]]++;
        }
        /*
        for (int i = 0; i < tmp;i++){
        cout << appear[i] << " ";
        }
        cout << endl;
        */
    }
    return 0;
}
