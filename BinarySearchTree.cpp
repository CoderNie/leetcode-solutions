#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BSTNode {
public:
  int start, end;
  BSTNode *left, *right;
  BSTNode(int s, int e, BSTNode* l, BSTNode* r):
    start(s), end(e), left(l), right(r) {}
};

// 731. My Calendar II
class MyCalendarTwo {
public:
  vector<pair<int, int>> books;
  vector<pair<int, int>> overlaps;
  MyCalendarTwo() {
  }
  bool book(int start, int end) {
    for (pair<int, int> overlap: overlaps) {
      if (max(overlap.first, start) < min(overlap.second, end)) {
        return false;
      }
    }
    for (pair<int, int> book: books) {
      if (max(book.first, start) < min(book.second, end)) {
        overlaps.push_back({max(book.first, start), min(book.second, end)});
      }
    }
    books.push_back({start, end});
    return true;
  }
  void output() {
    for (int i; i < books.size(); i++)
      cout << books[i].first << ", " << books[i].second << "\t";
    cout << endl;
    for (int i; i < overlaps.size(); i++)
      cout << overlaps[i].first << ", " << overlaps[i].second << "\t";
    cout << endl;
  }
};

class Solution {
public:
  // 718. Maximum Length of Repeated Subarray -- start one
  int findLength1(vector<int>& A, vector<int>& B) {
    int dp[A.size() + 1][B.size() + 1];
    for (int i = 0; i <= A.size(); i++)
      dp[i][B.size()] = 0;
    for (int j = 0; j <= B.size(); j++)
      dp[A.size()][j] = 0;
    int res = 0;
    for (int i = A.size() - 1; i >= 0; i--) {
      for (int j = B.size() - 1; j >= 0; j--) {
        if (A[i] == B[j]) dp[i][j] = dp[i + 1][j + 1] + 1;
        else dp[i][j] = 0;
        res = max(res, dp[i][j]);
      }
    }
    return res;
  }

  // 718. Maximum Length of Repeated Subarray -- end one
  int findLength(vector<int>& A, vector<int>& B) {
    int dp[A.size() + 1][B.size() + 1];
    for (int i = 0; i <= A.size(); i++)
      dp[i][0] = 0;
    for (int j = 0; j <= B.size(); j++)
      dp[0][j] = 0;
    int res = 0;
    for (int i = 0; i < A.size(); i++) {
      for (int j = 0; j < B.size(); j++) {
        if (A[i] == B[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
        else dp[i + 1][j + 1] = 0;
        res = max(res, dp[i + 1][j + 1]);
      }
    }
    return res;
  }

};


int main(){
  Solution s;
  vector<int> A = {1,2,3,2,1};
  vector<int> B = {3,2,1,4,7};
  cout << s.findLength(A, B) << endl;
  return 0;
}