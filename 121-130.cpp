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
    // 122. Best Time to Buy and Sell Stock II
    int maxProfit(vector<int>& prices) {
        int sum = 0;
        for (int now = 0; now + 1 < prices.size(); now++) {
            if (prices[now] < prices[now + 1])
                sum += (prices[now + 1] - prices[now]);
        }
        return sum;
    }
    // 123. Best Time to Buy and Sell Stock III
    int maxProfit2(vector<int>& prices) {
        int maxK = 2;
        int length = prices.size();
        if (length <= 0)
            return 0;
        int dp[maxK + 1][length];
        for (int ii = 0; ii < length; ii++)
            dp[0][ii] = 0;
        for (int k = 1; k <= maxK; k++)
            dp[k][0] = 0;
        for (int k = 1; k <= maxK; k++) {
            int maxSum = INT16_MIN;
            for (int ii = 1; ii < length; ii++) {
                // for (int jj = 0; jj < ii; jj++) {
                    int jj = ii - 1;
                    maxSum = max(maxSum, dp[k - 1][jj] - prices[jj]);
                // }
                dp[k][ii] = max(dp[k][ii - 1], maxSum + prices[ii]);
            }
        }
        return dp[maxK][length - 1];
    }

    // 124. Binary Tree Maximum Path Sum
    int maxPathSumVal;
    int maxPathSum(TreeNode* root) {
        maxPathSumVal = INT32_MIN;
        maxPathDown(root);
        return maxPathSumVal;
    }
    int maxPathDown(TreeNode* root) {
        if (root == NULL)
            return 0;
        int left = max(maxPathDown(root->left), 0);
        int right = max(maxPathDown(root->right), 0);
        maxPathSumVal = max(maxPathSumVal, left + right + root->val);
        return max(left, right) + root->val;
    }


    // 125. Valid Palindrome
    bool isAlphaNumeric(char ch) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
            return true;
        else
            return false;
    }
    char getLowerCase(char ch) {
        if (ch >= 'A' && ch <= 'Z')
            return ch - 'Z' + 'z';
        else
            return ch;
    }
    bool isPalindrome(string s) {
        int length = s.size();
        if (length <= 1)
            return true;
        int i = 0, j = length - 1;
        while (i < j) {
            while (!isAlphaNumeric(s[i]) && i < j)
                i++;
            while (!isAlphaNumeric(s[j]) && i < j)
                j--;
            if (i < j) {
                if (getLowerCase(s[i]) == getLowerCase(s[j])) {
                    i++;
                    j--;
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    // 126. Word Ladder II
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        
    }

    // 127. Word Ladder
    bool isValidTransform(string& before, string& after) {
        bool sum = false;
        for (int i = 0; i < before.size(); i++) {
            if (before[i] != after[i]) {
                if (sum == true) {
                    return false;
                } else {
                    sum = true;
                }
            }
        }
        return sum;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        vector<string> list = wordList;
        // word, depth
        queue<pair<string, int> > bfsQueue;
        bfsQueue.push({beginWord, 1});
        while (!bfsQueue.empty()) {
            string nowWord = bfsQueue.front().first;
            int nowDepth = bfsQueue.front().second;
            bfsQueue.pop();
            if (nowWord == endWord) {
                return nowDepth;
            }
            for (int i = 0; i < wordList.size(); i++) {
                if (isValidTransform(nowWord, wordList[i])){
                    bfsQueue.push({wordList[i], nowDepth + 1});
                    wordList.erase(wordList.begin() + i);
                    i--;
                }
            }
        }
        return 0;
    }

    // 128. Longest Consecutive Sequence
    int longestConsecutive(vector<int>& nums) {
        set<int> nums_set;
        for (int num : nums)
            nums_set.insert(num);
        int res = 0;
        for (int num : nums) {
            if (nums_set.find(num - 1) == nums_set.end()) {
                int count = 1;
                int now = num;
                while (nums_set.find(now + 1) != nums_set.end()) {
                    now++;
                    count++;
                }
                res = max(res, count);
            }
        }
        return res;    
    }

    // 129. Sum Root to Leaf Numbers
    void dfs(TreeNode* nowNode, int nowSum, int *totalSum) {
        nowSum = nowSum * 10 + nowNode->val;
        if (nowNode->left == NULL && nowNode->right == NULL) {
            *totalSum += nowSum;
        } else {
            if (nowNode->left != NULL)
                dfs(nowNode->left, nowSum, totalSum);
            if (nowNode->right != NULL)
                dfs(nowNode->right, nowSum, totalSum);
        }
    }
    int sumNumbers(TreeNode* root) {
        if (root == NULL)
            return 0;
        int totalSum = 0;
        dfs(root, 0, &totalSum);
        return totalSum;
    }

    // 130. Surrounded Regions
    void solve(vector<vector<char> >& board) {
        if (board.size() <= 2 || board[0].size() <= 2) {
            return;
        }
        int height = board.size(), width = board[0].size();
        bool isVisited[height][width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                isVisited[i][j] = false;
        for (int i = 0; i < height; i++) {
            for (int j =  0; j < width; j++) {
                if (isVisited[i][j] || board[i][j] == 'X') {
                    continue;
                } else {
                    vector<pair<int, int> > dots;
                    queue<pair<int, int> > bfsQueue;
                    bfsQueue.push({i, j});
                    isVisited[i][j] = true;
                    bool isBorder = false;
                    while (!bfsQueue.empty()) {
                        pair<int, int> nowNode = bfsQueue.front();
                        int x = nowNode.first, y = nowNode.second;
                        bfsQueue.pop();
                        // cout << "x = " << x << " , y = " << y << endl;
                        if (!isBorder && (x == 0 || x == height - 1 || y == 0 || y == width - 1)) {
                            isBorder = true;
                        }
                        if (!isBorder)
                            dots.push_back(nowNode);
                        // top
                        if (x - 1 >= 0 && board[x - 1][y] == 'O' && !isVisited[x - 1][y]) {
                            bfsQueue.push({x - 1, y});
                            isVisited[x - 1][y] = true;
                        }
                        // bottom
                        if (x + 1 < height && board[x + 1][y] == 'O' && !isVisited[x + 1][y]) {
                            bfsQueue.push({x + 1, y});
                            isVisited[x + 1][y] = true;
                        }
                        // left
                        if (y - 1 >= 0 && board[x][y - 1] == 'O' && !isVisited[x][y - 1]) {
                            bfsQueue.push({x, y - 1});
                            isVisited[x][y - 1] = true;
                        }
                        // right
                        if (y + 1 < width && board[x][y + 1] == 'O' && !isVisited[x][y + 1]) {
                            bfsQueue.push({x, y + 1});
                            isVisited[x][y + 1] = true;
                        }
                    }
                    if (!isBorder) {
                        for (int k = 0; k < dots.size(); k++) {
                            board[dots[k].first][dots[k].second] = 'X';
                        }
                    }
                }
            }
        }
    }
    
    void printMatrix(vector<vector<char>> &mat) {
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[i].size(); j++) {
                cout << mat[i][j] << ", ";
            }
            cout << endl;
        }
    }
    
};

//     1
//    / \
//   5   1
//        \
//         6
int main() {
    Solution s;
    vector<vector<char> > arr = {{'O','O','O','O','O','O','O','O','X','O','O','O','O','O','X','O','O','O','O','O'},{'O','O','O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O'},{'X','O','O','X','O','X','O','O','O','O','X','O','O','X','O','O','O','O','O','O'},{'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','X','X','O'},{'O','X','X','O','O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O'},{'O','O','O','O','X','O','O','O','O','O','O','X','O','O','O','O','O','X','X','O'},{'O','O','O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O'},{'O','O','O','O','O','O','O','O','O','O','O','O','O','X','O','O','O','O','O','O'},{'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','X','O'},{'O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O'},{'O','O','O','O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O'},{'O','O','O','O','X','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O'},{'O','O','O','O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O'},{'X','O','O','O','O','O','O','O','O','X','X','O','O','O','O','O','O','O','O','O'},{'O','O','O','O','O','O','O','O','O','O','O','X','O','O','O','O','O','O','O','O'},{'O','O','O','O','X','O','O','O','O','O','O','O','O','X','O','O','O','O','O','X'},{'O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','X','O','X','O','O'},{'O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O'},{'O','O','O','O','O','O','O','O','X','X','O','O','O','X','O','O','X','O','O','X'},{'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O'}};
    s.printMatrix(arr);
    s.solve(arr);
    s.printMatrix(arr);
    return 0;
}