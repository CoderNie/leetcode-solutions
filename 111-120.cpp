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

  // 112. Path Sum
  bool hasPathSum(TreeNode* root, int sum) {
    if (root == NULL) {
      return false;
    } else {
      if (root->left == NULL && root->right == NULL) {
        return root->val == sum;
      } else {
        sum -= root->val;
        return (root->left != NULL && hasPathSum(root->left, sum)) || (root->right != NULL && hasPathSum(root->right, sum));
      }
    }
  }

  // 113. Path Sum II
  vector<vector<int> > pathSum(TreeNode* root, int sum) {
    if (root == NULL) return {};
    stack<TreeNode*> myStack;
    map<TreeNode*, bool> visited;
    vector<stack<TreeNode*> > resultStacks;
    myStack.push(root);
    int mySum = root->val;
    while (!myStack.empty()) {
      TreeNode* nowNode = myStack.top();
      if (nowNode->left != NULL && visited.find(nowNode->left) == visited.end()) {
        visited[nowNode->left] = true;
        myStack.push(nowNode->left);
        mySum += nowNode->left->val;
      } else if (nowNode->right != NULL && visited.find(nowNode->right) == visited.end()) {
        visited[nowNode->right] = true;
        myStack.push(nowNode->right);
        mySum += nowNode->right->val;
      } else {
        if (nowNode->left == NULL && nowNode->right == NULL && mySum == sum) {
          stack<TreeNode*> resultStack = myStack;
          resultStacks.push_back(resultStack);
        }
        mySum -= nowNode->val;
        myStack.pop();
      }
    }
    vector<vector<int> > results;
    for (int i = 0; i < resultStacks.size(); i++) {
      vector<int> result;
      while (!resultStacks[i].empty()) {
        result.push_back(resultStacks[i].top()->val);
        resultStacks[i].pop();
      }
      reverse(result.begin(), result.end());
      results.push_back(result);
    }
    return results;
  }

  // 114. Flatten Binary Tree to Linked List
  void flatten(TreeNode* root) {
    flatten114(root);
  }

  pair<TreeNode*, TreeNode*> flatten114(TreeNode* root) {
    if (root == NULL) {
      return {NULL, NULL};
    } else {
      pair<TreeNode*, TreeNode*> leftPair, rightPair;
      TreeNode* rear = root;
      leftPair = flatten114(root->left);
      rightPair = flatten114(root->right);
      // ------------------ very important
      root->left = NULL;
      root->right = NULL;
      // ------------------
      if (leftPair.first != NULL) {
        root->right = leftPair.first;
        rear = leftPair.second;
      }
      if (rightPair.first != NULL) {
        if (leftPair.second != NULL) {
          leftPair.second->right = rightPair.first;
        } else {
          root->right = rightPair.first;
        }
        rear = rightPair.second;
      }
      return {root, rear};
    }
  }


}