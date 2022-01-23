// AC 2021-08-05 22:01:21
/*sample input
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255
*/
/*sample output
1
3
255
*/
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <climits>
using namespace std;
int post_order[10004];
int in_order[10004];
int lch[10004];
int rch[10004];
int n = 0;
// in climits
int ans_sum = INT_MAX;
int ans = 0;
bool read_tree(int* arr){
    n = 0;
    string str;
    getline(cin, str);
    stringstream ss;
    ss << str;
    while(ss >> arr[n])
        n++;
    return n > 0;
}
// 1 for post_order range, 2 for in_order range
int build_tree(int L1, int R1, int L2, int R2){
    if(R2 < L2) // we can only deduce by in_order tree
        return 0; // no child
    int root = post_order[R1];
    int div = L2;
    int p = div;
    while(in_order[div] != root)
        div++;
    int left_n = div - p;
    
    lch[root] = build_tree(L1, L1 + left_n - 1, L2, div - 1);
    rch[root] = build_tree(L1 + left_n, R1 - 1, div + 1, R2);
    return root;
}
void getans(int root, int sum){
    if(!lch[root] && !rch[root]){
        sum += root;
        //printf("checking leaf %d\n", root);
        if(sum <= ans_sum)
        {
         //   printf("renew ans_sum = %d to %d\n", ans_sum, sum);
            if(sum == ans_sum)
                ans = min(ans, root);
            else
                ans = root;
            ans_sum = sum;
        }
        return;
    }
    if(lch[root])
        getans(lch[root], sum + root);
    if(rch[root])
        getans(rch[root], sum + root);
}
int main(){
    while(read_tree(in_order)){
        read_tree(post_order);
        ans_sum = INT_MAX;
        memset(lch, 0, sizeof(lch));
        memset(rch, 0, sizeof(rch));
        build_tree(0, n - 1, 0, n - 1);
       /* 
        for (int i = 0; i < n; i++){
            printf("index: %d lch: %d rch: %d\n", in_order[i], lch[in_order[i]], rch[in_order[i]]);
        }
        */
        getans(post_order[n - 1], 0);
        printf("%d\n", ans);
    }
    return 0;
}