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

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  // 61. Rotate List
  ListNode* rotateRight(ListNode* head, int k) {
    if (head == NULL || head->next == NULL) return head;
    ListNode *p = head;
    int length = 1;
    while (p->next != NULL) {
      length++;
      p = p->next;
    }
    p->next = head;
    k = k % length;
    p = head;
    for (int i = 1; i < length - k; i++)
      p = p->next;
    head = p->next;
    p->next = NULL;
    return head;
  }

  // 62. Unique Paths
  int uniquePaths(int m, int n) {
    if (m <= 1 || n <= 1) return 1;
    int dp[m][n];
    for (int i = 0; i < m; i++)
      dp[i][0] = 1;
    for (int j = 0; j < n; j++)
      dp[0][j] = 1;
    for (int i = 1; i < m; i++)
      for (int j = 1; j < n; j++)
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    return dp[m - 1][n - 1];   
  }

  // 63. Unique Paths II
  int uniquePathsWithObstacles(vector<vector<int> >& obstacleGrid) {
    if (obstacleGrid.size() < 1 || obstacleGrid[0].size() < 1) return 0;
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    int dp[m][n];
    dp[0][0] = (obstacleGrid[0][0] == 0) ? 1 : 0;
    for (int i = 1; i < m; i++)
      dp[i][0]  = (obstacleGrid[i][0] == 0) ? dp[i - 1][0] : 0;
    for (int j = 1; j < n; j++)
      dp[0][j]  = (obstacleGrid[0][j] == 0) ? dp[0][j - 1] : 0;
    for (int i = 1; i < m; i++)
      for (int j = 1; j < n; j++)
        dp[i][j] = (obstacleGrid[i][j] == 0) ? (dp[i - 1][j] + dp[i][j - 1]) : 0;
    return dp[m - 1][n - 1];
  }

  // 66. Plus One
  vector<int> plusOne(vector<int>& digits) {
    vector<int> result = digits;
    int p = result.size() - 1;
    int remain = 1;
    while (remain > 0 && p >= 0) {
      result[p] += remain;
      remain = result[p] / 10;
      result[p--] %= 10;
    }
    if (remain > 0)
      result.insert(result.begin(), remain);
    return result;
  }

  void printArr(vector<int> & arr){
    for (int i = 0; i < arr.size(); i++) 
      cout << arr[i];
    cout << endl;
  }

  // 68. Text Justification
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> result;
    queue<string> lineQueue;
    string word, lineStr, spaceStr;
    int nowWidth = 0;
    for (int i = 0; i < words.size(); i++) {
      int nowSize = words[i].size();
      // 如果当前队列中字符串的长度足够一行
      if (!lineQueue.empty() && nowWidth <= maxWidth && nowWidth + nowSize + 1 > maxWidth) {
        lineStr = "";
        spaceStr = " ";
        if (lineQueue.size() > 1) {
          int space = (maxWidth - nowWidth) / (lineQueue.size() - 1);
          int remain = (maxWidth - nowWidth) % (lineQueue.size() - 1);
          for (int k = 0; k < space; k++)
            spaceStr += " ";
          while (lineQueue.size() > 1) {
            word = lineQueue.front();
            lineQueue.pop();
            lineStr += word + spaceStr;
            if (remain-- > 0) lineStr += " ";
          }
          lineStr += lineQueue.front();
        } else {
          lineStr = lineQueue.front();
          while (lineStr.size() < maxWidth) lineStr += " ";
        }
        lineQueue.pop();
        result.push_back(lineStr);
        nowWidth = nowSize;
      } else {
        if (lineQueue.empty()) nowWidth += nowSize;
        else nowWidth += nowSize + 1;
      }
      lineQueue.push(words[i]);
    }
    // 处理剩余的字符串
    lineStr = "";
    while (lineQueue.size() > 1) {
      lineStr += lineQueue.front() + " ";
      lineQueue.pop();
    }
    if (!lineQueue.empty()) {
      lineStr += lineQueue.front();
      while (lineStr.size() < maxWidth)
        lineStr += " ";
      result.push_back(lineStr);
    }
    return result;
  }

  // 69. Sqrt(x)
  int mySqrt(int x) {
    long start = 0, end = x, mid;
    while (start < end) {
      mid = (start + end) / 2;
      if (mid * mid > x) {
        end = mid - 1;
      } else if (mid * mid < x) {
        start = mid + 1;
      } else {
        return mid;
      }
    }
    return (start * start <= x) ? start : (start - 1);
  } 
};

int main() {
  Solution s;
  vector<string> words = {"Listen","to","many,","speak","to","a","few."};
  int maxWidth = 6;
  words = s.fullJustify(words, maxWidth);
  for (int i = 0; i < words.size(); i++)
    cout << "\"" << words[i] << "\"" << endl;
  return 0;
}