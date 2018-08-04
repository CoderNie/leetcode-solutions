#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <stack>

#include <algorithm>
#include <sstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <climits>

using namespace std;

/**
Definition for a binary tree node. */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  // 101. Symmetric Tree
  bool isEqual(TreeNode* left, TreeNode* right) {
    if (left == NULL && right == NULL) {
      return true;
    } else if (left != NULL && right != NULL && left->val == right->val) {
      return isEqual(left->right, right->left) && isEqual(left->left, right->right);
    } else {
      return false;
    }
  }
  bool isSymmetric(TreeNode* root) {
    if (root == NULL) return true;
    else return isEqual(root->left, root->right);
  }

  // 102. Binary Tree Level Order Traversal
  vector<vector<int> > levelOrder(TreeNode* root) {
    vector<vector<int> > results;
    if (root == NULL) return results;
    queue<pair<TreeNode*, int> > bfsQueue;
    bfsQueue.push({root, 1});
    pair<TreeNode*, int> nowPair;
    TreeNode* nowNode;
    int nowLevel;
    while (!bfsQueue.empty()) {
      nowPair = bfsQueue.front();
      nowNode = nowPair.first;
      nowLevel = nowPair.second;
      bfsQueue.pop();
      if (nowLevel > results.size()) results.push_back({});
      results[nowLevel - 1].push_back(nowNode->val);
      if (nowNode->left != NULL) bfsQueue.push({nowNode->left, nowLevel + 1});
      if (nowNode->right != NULL) bfsQueue.push({nowNode->right, nowLevel + 1});
    }
    return results;
  }

  // 104. Binary Tree Zigzag Level Order Traversal
  vector<vector<int> > zigzagLevelOrder(TreeNode* root) {
    vector<vector<int> > results = levelOrder(root);
    for (int i = 1; i < results.size(); i += 2)
      reverse(results[i].begin(), results[i].end());
    return results;
  }

  // 105. Construct Binary Tree from Preorder and Inorder Traversal
  TreeNode* buildTree_old(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.size() <= 0) return NULL;
    map<int, int> posMap;
    for (int i = 0; i < inorder.size(); i++)
      posMap[inorder[i]] = i;
    TreeNode *root = new TreeNode(preorder[0]), *p, *before;
    for (int i = 1; i < preorder.size(); i++) {
      TreeNode *newNode = new TreeNode(preorder[i]);
      p = root;
      while (true) {
        if (posMap[newNode->val] > posMap[p->val]) {
          if (p->right == NULL) {
            p->right = newNode;
            break;
          } else {
            p = p->right;
          }
        } else {
          if (p->left == NULL) {
            p->left = newNode;
            break;
          } else {
            p = p->left;
          }
        }
      }
    }
    return root;
  }

  // 105. Construct Binary Tree from Preorder and Inorder Traversal
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildTreeOnce(preorder, 0, preorder.size(), inorder, 0, inorder.size());
  }
  int indexOf(int target, vector<int>& arr, int arrStart) {
    for (int i = arrStart; i < arr.size(); i++)
      if (target == arr[i]) return i;
    return -1;
  }
  TreeNode* buildTreeOnce(vector<int>& preorder, int pStart, int pEnd, vector<int>& inorder, int iStart, int iEnd) {
    if (pEnd - pStart <= 0) {
      return NULL;
    } else {
      int nowIndex = indexOf(preorder[pStart], inorder, iStart);
      int leftLength = nowIndex - iStart;
      TreeNode *nowNode = new TreeNode(preorder[pStart]);
      nowNode->left = buildTreeOnce(preorder, pStart + 1, pStart + leftLength + 1, inorder, iStart, nowIndex);
      nowNode->right = buildTreeOnce(preorder, pStart + leftLength + 1, pEnd, inorder, nowIndex + 1, iEnd);
      return nowNode;
    }
  }
};