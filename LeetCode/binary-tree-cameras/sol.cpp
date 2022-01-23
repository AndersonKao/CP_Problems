#include <bits/stdc++.h>
using namespace std;
//   Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 // 0: Strict ST; All nodes below this are covered, but not this one
 //
 // 1: Normal ST; All nodes below and incl this are covered - no camera
 // 2: Placed camera; All nodes below this are covered, plus camera here
// [State 0] Strict subtree: All the nodes below this node are covered, but not this node.
// [State 1] Normal subtree: All the nodes below and including this node are covered, but there is no camera here.
// [State 2] Placed camera: All the nodes below and including this node are covered, and there is a camera here (which may cover nodes above this node).
class Solution {
public:
    int minCameraCover(TreeNode* root) {
        int u, v, w;
        tie(u, v, w) = solve(root);
        return min(v, w);
    }
    tuple<int, int, int> solve(TreeNode * node){
        if(node == nullptr)
            return tuple<int, int, int>(0, 0, 900000);
        int L[3];
        int R[3];
        tie(L[0], L[1], L[2]) = solve(node->left);
        tie(R[0], R[1], R[2]) = solve(node->right);
        int mL, mR;
        mL = min(L[1], L[2]);
        mR = min(R[1], R[2]);
        int state[3];
        state[0] = L[1] + R[1]; // 下面必定沒有camera
        state[1] = min(L[2] + mR, R[2] + mL); // 可以是左邊有camera, 右邊隨意 或者反過來
        state[2] = 1 + min(L[0], mL) + min(R[0], mR); // 反正這個點已經有camera了，左右有沒有無關，就取最小
        return tuple<int, int, int>(state[0], state[1], state[2]);
    }

};