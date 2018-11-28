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

    // 111. Minimum Depth of Binary Tree
    int minDepth(TreeNode* root) {
        if (root == NULL)
            return 0;
        queue<pair<TreeNode*, int> > bfsQueue;
        bfsQueue.push({root, 1});
        while (!bfsQueue.empty()) {
            TreeNode* nowNode = bfsQueue.front().first;
            int nowDepth = bfsQueue.front().second;
            bfsQueue.pop();
            if (nowNode->left == NULL && nowNode->right == NULL)
                return nowDepth;
            if (nowNode->left != NULL)
                bfsQueue.push({nowNode->left, nowDepth + 1});
            if (nowNode->right != NULL)
                bfsQueue.push({nowNode->right, nowDepth + 1});
        }
        return 0;
    }

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

    unordered_map<string, int> cacheMap;
    // 115. Distinct Subsequences
    int numDistinct(string s, string t) {
        if (cacheMap.find(s + "&" + t) != cacheMap.end())
            return cacheMap[s + "&" + t];
        if (s.size() < t.size())
            return 0;
        if (s.size() == t.size()) {
            if (s == t) {
                return 1;
            } else {
                return 0;
            }
        }
        int sum = 0;
        if (t.size() == 1) {
            for (int i = 0; i < s.size(); i++)
                if (s[i] == t[0])
                    sum++;
        } else {
            for (int i = 0; i <= s.size() - t.size(); i++) {
                if (s[i] == t[0]) {
                    // cout << s.substr(i + 1) << ",,," << t.substr(1) << endl;
                    sum += numDistinct(s.substr(i + 1), t.substr(1));
                }
            }
        }1
        cacheMap[s + "&" + t] = sum;
        return sum;
    }        

    // 118. Pascal's Triangle
        vector<vector<int>> generate(int numRows) {
            if (numRows == 0) {
                return {};
            } else {
                vector<vector<int> > res = {{1}};
                for (int i = 1; i < numRows; i++) {
                    vector<int> newRow = {1};
                    for (int j = 1; j < i; j++) {
                        newRow.push_back(res[i - 1][j - 1] + res[i - 1][j]);
                    }
                    newRow.push_back(1);
                    res.push_back(newRow);
                }
                // res.insert(res.begin(), {});
                return res;
            }
        }
        // 119. Pascal's Triangle 2
        vector<int> getRow(int rowIndex) {
            vector<int> res = {};
            for (int i = 0; i <= rowIndex; i++) {
                res.insert(res.begin(), 1);
                for (int j = 1; j < i; j++) {
                    res[j] = res[j] + res[j + 1];
                }
            }
            return res;
        }

        void printArr(vector<int> &arr) {
            for (int i = 0; i < arr.size(); i++) {
                cout << arr[i] << ", ";
            }
            cout << endl;
        }
    };
    int main () {
        int n = 4;
        Solution solution;
        string s, t;
        while (cin >> s >> t) {
            cout << solution.numDistinct(s, t) << endl;
        }
        return 0;
    }