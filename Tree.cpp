#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  // 94. Binary Tree Inorder Traversal
  vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> inorderStack;  
    vector<int> res;
    TreeNode* p = root;
    while (p != NULL || !inorderStack.empty()) {
      while (p != NULL) {
        inorderStack.push(p);
        p = p->left;
      }
      if (!inorderStack.empty()){
        p = inorderStack.top();
        inorderStack.pop();
        res.push_back(p->val);
        p = p->right;
      }
    }
    return res;
  }

  bool isReachable(vector<vector<pair<int, int> > >& dataList, int start, int end, int mark) {
    queue<pair<int, vector<int> > > bfsQueue;
    for (int i = 0; i < dataList[start].size(); i++) {
      if (dataList[start][i].first != end) {
        pair<int, vector<int> > myPair;
        myPair.first = dataList[start][i].first;
        myPair.second = {dataList[start][i].second, mark};
        bfsQueue.push(myPair);
      }
    }
    while (!bfsQueue.empty()) {
      int nowPoint = bfsQueue.front().first;
      vector<int> nowPath = bfsQueue.front().second;
      bfsQueue.pop();
      // cout << nowPoint << endl;
      if (nowPoint == end) {
        return true;
      } else {
        for (int i = 0; i < dataList[nowPoint].size(); i++) {
          int nowPathIndex = dataList[nowPoint][i].second;
          bool flag = true;
          for (int j = 0; j < nowPath.size(); j++) {
            // cout << "nowPath[" << j << "] = " << nowPath[j] << endl;
            if (nowPathIndex == nowPath[j]) {
              flag = false;
              break;
            }
          }
          if (flag) {
            pair<int, vector<int> > myPair;
            myPair.first = dataList[nowPoint][i].first;
            myPair.second = nowPath;
            myPair.second.push_back(dataList[nowPoint][i].second);
            bfsQueue.push(myPair);
          }
        }
      }
    }
    return false;
  }

  // 684. Redundant Connection
  vector<int> findRedundantConnection(vector<vector<int> >& edges) {
    vector<vector<pair<int, int>>> dataList;
    for (int i = 0; i < edges.size(); i++) {
      if (edges[i][1] + 1 > dataList.size()) {
        dataList.resize(edges[i][1] + 1);
      }
      pair<int, int> p1(edges[i][1], i), p2(edges[i][0], i);
      dataList[edges[i][0]].push_back(p1);
      dataList[edges[i][1]].push_back(p2);
      // if (i == 0) {
      //   cout << "i = 0 here: " << edges[i][0] << ", " << p1.second << endl;
      // }
    }
    // for (int i = 1; i < dataList.size(); i++) {
    //   for (int j = 0; j < dataList[i].size(); j++) {
    //     cout << "dataList[" << i << "][" << j << "]"<< dataList[i][j].first << "\t" << dataList[i][j].second << endl;
    //   }
    // }
    for (int i = edges.size() - 1; i >= 0; i--) {
      if (isReachable(dataList, edges[i][0], edges[i][1], i)) {
        return edges[i];
      }
    }
    return edges[0];
  }

  string afterS (string S) {
      string SA = "";
      for (int i = 0; i < S.size(); i++) {
          if (S[i] != '#') {
              SA += S[i];
          } else if (SA.size() > 0) {
              SA = SA.substr(0, SA.size() - 1);
          }
      }
      cout << SA << endl;
      return SA;
  }
  bool backspaceCompare(string S, string T) {
      string SA = afterS(S);
      string TA = afterS(T);
      return !SA.compare(TA);
  }

  // 845. 数组中的最长山脉
  int longestMountain(vector<int>& A) {
    int max = 0;
    for (int i = 1; i + 1 < A.size(); i++) {
      int a = 0, b = 0;
      for (int j = i - 1; j >= 0; j--) {
        if (A[j] < A[j + 1]) a++;
        else break;
      }
      for (int k = i + 1; k < A.size(); k++) {
        if (A[k] < A[k - 1]) b++;
        else break;
      } 
      if (a > 0 && b > 0 && a + b + 1 > max) max = a + b + 1;
    }
    return max;
  }
};


int main() {
  Solution s;
  vector<int> test = {0,1,3,4,5};
  cout << s.longestMountain(test) << endl;
  // vector<vector<int>> edges = {{4,5}, {1,2}, {2,4}, {3,4}, {2,3}};
  // vector<int> ans = s.findRedundantConnection(edges);
  // cout << ans[0] << "\t" << ans[1] << endl;
  // cout <<a  << endl;
  return 0;
}