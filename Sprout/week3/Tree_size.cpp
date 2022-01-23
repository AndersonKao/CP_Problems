/*
   some member functions of vector:

   1. clear()        : clear the array
   2. size()         : number of elements in the array
   3. push_back(val) : push val to the back of the array
   4. pop_back()     : remove the last element of the array
*/

#include <stdio.h>
#include <vector>

std::vector<int> child[100001]; 
   // node id 's children are 
   // child[id][0], child[id][1] ... 
   // child[id][child[id].size()-1]
int sum[100001];  // sum[i]: node i has sum[i] children

void dfs(int id, int parent){
   sum[id] = 1;
   for(int i=0, n=child[id].size(); i<n; ++i){
      if(child[id][i] == parent) continue;
      dfs(child[id][i], id);
      sum[id] += sum[child[id][i]];
   }
}

int main(){
   int T, n;
   int a, b;
   scanf("%d", &T);
   while(T--){
      scanf("%d", &n);
      for(int i=0; i<n; ++i) child[i].clear(); // init
      for(int i=0; i<n-1; ++i){
         scanf("%d%d", &a, &b);
         child[a].push_back(b);
         child[b].push_back(a);
      }
      dfs(0, 0);
      for(int i=0; i<n; ++i) printf("node %d: %d\n", i, sum[i]);
   }
}
