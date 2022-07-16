#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
int fcmp(double a, double b){
    if(abs(a- b) < eps)
        return 0;
    return (a > b) * 2 - 1;
}
auto cmp = [](int a, int b)
{
    return (a % 5 < b % 5);
};
int main()
{
    int T = 508;


    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    for (int i = 0; i < 100; i++)
        pq.emplace(rand() % 10000);
    vector<int> V1(pq.size());
    copy(&(pq.top()), (&pq.top()) + pq.size(), V1.begin());
    for(int &e:V1){
        cout << e << " ";
    }
    cout << endl;
    while(pq.size()){
        cout << pq.top() << " ";
        pq.pop();
    }
    /*
    for(double &e: V1)
        cin >> e;
    for(double &e: V2)
        cin >> e;
    for (int i = 0; i < T; i++){
        if(fcmp(V1[i], V2[i]) != 0){
            printf("%dth %.10f, %.10f\n", i, V1[i], V2[i]);
        }
    }
    */
}