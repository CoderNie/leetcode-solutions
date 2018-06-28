#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include <algorithm>
#include <sstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <climits>

using namespace std;

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
  bool isValueSuitable (vector<vector<char> >& board, int i, int j, char value) {
    for (int k = 0; k < 9; k++) {
      if (board[i][k] == value) return false;
      if (board[k][j] == value) return false;
    }
    int startP = i / 33, startQ = j / 33;
    for (int p = startP; p < startP + 3; p++)
      for (int q = startQ; q < startQ + 3; q++)
        if (board[p][q] == value) return false;
    return true;
  }
  bool backTracking(vector<vector<char> >& board) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.') {
          for (char c = '1'; c <= '9'; c++) {
            if (isValueSuitable(board, i, j, c)) {
              board[i][j] = c;
              if (backTracking(board)) {
                return true;
              } else {
                board[i][j] = '.';
              }
            }
          }
          return false;
        }
      }
    }
    return true;
  }

  // 37. Sudoku Solver
  void solveSudoku(vector<vector<char> >& board) {
    backTracking(board);
  }
  void printBoard(vector<vector<char> >& board) {
    for (int i = 0; i < board.size(); i++){ 
      for (int j = 0; j < board[0].size(); j++) 
        cout << board[i][j] << '\t';
      cout << endl;
    }
  }

  // 41. First Missing Positive
  int firstMissingPositive(vector<int>& nums) {
    vector<int> bin(nums.size() + 1, 0);
    for (int num : nums) {
      if (num > 0 && num < bin.size()) {
        bin[num] = 1;
      }
    }    
    for (int i = 1; i < bin.size(); i++) {
      if (bin[i] == 0) {
        return i;
      }
    }
    return bin.size();
  }
  // 42. Trapping Rain Water
  int trap(vector<int>& height) {
    if (height.size() == 0) return 0;
    int res = 0, leftMax, rightMax;
    for (int i = 1; i < height.size() - 1; i++) {
      leftMax = 0;
      for (int j = i - 1; j >= 0; j--) {
        if (height[j] > leftMax) leftMax = height[j];
      }
      rightMax = 0;
      for (int j = i + 1; j < height.size(); j++) {
        if (height[j] > rightMax) rightMax = height[j];
      }
      if (leftMax > height[i] && rightMax > height[i]) {
        res += min(leftMax, rightMax) - height[i];
      }
    }
    return res;
  }
  // 44. Wildcard Matching
  /*
    dp[i][j] represents isMatch(s.substr(0, i), p.substr(0, j))
    if (p[j - 1] == '*') dp[i][j] = dp[i][j - 1] || dp[i - 1][j]
    if (p[j - 1] == '?') dp[i][j] = dp[i - 1][j - 1]

    intiail:
    if (i > 0) dp[i][0] = false
    if (j > 0) if (p[j - 1] == '*') dp[0][j] = dp[0][j - 1]
  */
  bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    bool dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= m; j++)
        dp[i][j] = false;
    
    dp[0][0] = true;
    for (int j = 1; j <= m; j++) 
      if (p[j - 1] == '*')
        dp[0][j] = dp[0][j - 1];
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (p[j - 1] == '*') {
          dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
        } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        }
        // cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
      }
    }
    return dp[n][m];
  }
  // 45. Jump Game II || BFS TLE
  int jump_bfs(vector<int>& nums) {
    int lastIndex = nums.size() - 1;
    if (lastIndex <= 0) return 0;
    /* index stepCnt */
    queue< pair<int, int> > bfsQueue;
    bool isPassed[lastIndex + 1];
    for (int i = 0; i <= lastIndex; i++)
      isPassed[i] = false;
    bfsQueue.push({0, 0});
    isPassed[0] = true;
    while (!bfsQueue.empty()) {
      int nowIndex = bfsQueue.front().first;
      int stepCnt = bfsQueue.front().second;
      bfsQueue.pop();
      if (nowIndex == lastIndex) return stepCnt;
      for (int i = nums[nowIndex]; i >= 1; i--) {
        if (nowIndex + i <= lastIndex && !isPassed[nowIndex + i]) {
          isPassed[nowIndex + i] = true;
          bfsQueue.push({nowIndex + i, stepCnt + 1});
        }
      }
    }
    return 0;
  }
  // 45. Jump Game II
  int jump(vector<int> & nums) {
    int length = nums.size();
    if (length <= 1) return 0;
    int curEnd = 0, curFarthest = 0, result = 0;
    for (int i = 0; i < length - 1; i++) {
      curFarthest = max(curFarthest, i + nums[i]);
      if (i == curEnd) {
        result++;
        if (curFarthest >= length - 1) return result;
        else curEnd = curFarthest;
      }
    }
    return result;
  }

  bool place(int i, int *x) {
    for (int j = 0; j < i; j++)
      if (x[i] == x[j] || abs(x[i] - x[j]) == i - j)
        return false;
    return true;
  }
  vector<string> getOutput(int *x, int n) {
    string s = "";
    for (int i = 0; i < n; i++)
      s += '.';
    vector<string> res(n, s);
    for (int i = 0; i < n; i++)
      res[i][x[i]] = 'Q';
    return res;
  }
  // 51. N-Queens
  vector<vector<string> > solveNQueens(int n) {
    vector<vector<string> > results;
    if (n <= 0) return results;
    int x[n];
    for (int i = 0; i < n; i++)
      x[i] = 0;
    int i = 0;
    while (true) {
      while (x[i] < n) {
        if (place(i, x)) {
          if (i == n - 1) {
            results.push_back(getOutput(x, n));
            break;
          } else {
            i++;
            // x[i] = 0;
          }
        } else {
          x[i]++;
        }
      }
      x[i] = 0;
      i--;
      if (i < 0) {
        break;
      } else {
        x[i]++;
      }
    }
    return results;
  }
  // 52. N-Queens II
  void backTrackQueue(int i, int n, int *result, int *x) {
    if (i == n) {
      *result = *result + 1;
    } else {
      for (int j = 0; j < n; j++) {
        x[i] = j;
        if (place(i, x)) {
          backTrackQueue(i + 1, n, result, x);
        }
      }
    }
  }
  int totalNQueens(int n) {
    int result = 0;
    if (n <= 0) return result;
    int x[n];
    for (int i = 0; i < n; i++)
      x[i] = 0;
    backTrackQueue(0, n, &result, x);
    return result;
  }
  // 57. Insert Interval
  vector<Interval> insert_origin(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> results = intervals;
    int length = results.size();
    if (length <= 0) {
      results.push_back(newInterval);
    } else {
      bool isInserted = false;
      for (int i = 0; i < results.size(); i++) {
        if (!isInserted) {
          if (max(newInterval.start, results[i].start) <= min(newInterval.end, results[i].end)) {
            results[i].start = min(newInterval.start, results[i].start);
            results[i].end = max(newInterval.end, results[i].end);
            isInserted = true;
          } else if (newInterval.end < results[i].start) {
            results.insert(results.begin() + i, newInterval);
            isInserted = true;
            i++;
          }
        } else {
          if (results[i - 1].end < results[i].start) {
            break;
          } else {
            results[i - 1].start = min(results[i - 1].start, results[i].start);
            results[i - 1].end = max(results[i - 1].end, results[i].end);
            results.erase(results.begin() + i);
            i--;
          }
        }
      }
      if (!isInserted) {
        results.push_back(newInterval);
      }
    }
    return results;
  }
  // 57. Insert Interval || rectified
  vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> results = {newInterval};
    for (auto p : intervals) {
      auto & q = results.back();
      if (max(p.start, q.start) <= min(p.end, q.end)) {
        q.start = min(p.start, q.start);
        q.end = max(p.end, q.end);
      } else {
        if (p.end < q.start) swap(p, q);
        results.push_back(p);
      }
    }
    return results;
  }
  // 65. Valid Number
  bool isNumber(string s) {
    bool isStartOver = false, isNumOver = false, isDotted = false, isExp = false, isNeg = false;
    char c;
    for (int i = 0; i < s.size(); i++) {
      c = s[i];
      if (c == ' ') {
        if (isStartOver) {
          if (!isNumOver) {
            isNumOver = true;
          }
        } else {
          if (isNeg) {
            return false;
          }
        }
      } else {
        if (isNumOver) return false;
        if (c == 'e') {
          if (!isStartOver || isExp || i + 1 == s.size()) {
            return false;
          } else {
            isExp = true;
            isNeg = false;
            isStartOver = false;
          }
        } else if (c == '.') {
          if (isDotted || isExp || (!isStartOver && (i + 1 == s.size() || s[i + 1] < '0' || s[i + 1] > '9'))) {
            return false;
          } else {
            isStartOver = true;
            isDotted = true;
          }
        } else if (c >= '0' && c <= '9') {
          if (!isStartOver) isStartOver = true;
        } else if (c == '-' || c == '+') {
          if (isStartOver || isNeg) {
            return false;
          } else {
            isNeg = true;
          }
        } else {
          return false;
        }
      }
    }
    if (isStartOver) {
      return true;
    } else {
      return false;
    }
  }

  int minDistance(string word1, string word2) {
    int n = word1.size(), m = word2.size();
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
      dp[i][0] = i;
    for (int j = 0; j <= m; j++)
      dp[0][j] = j;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        if (word1[i - 1] == word2[j - 1]) 
          dp[i][j] = dp[i - 1][j - 1];
        else 
          dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
    return dp[n][m];
  }
  // 97. Interleaving String
    /*
    i + j = k
    dp[i][j][k] = (dp[i - 1][j][k - 1] && s1[i - 1] == s3[k - 1]) || (dp[i][j - 1][k - 1] && s2[j - 1] == s3[k - 1])
    dp[i][0][i] = dp[i - 1][0][i - 1] && s1[i - 1] == s3[i - 1]
    dp[0][j][j] = dp[0][j - 1][j - 1] && s2[j - 1] == s3[j - 1]
  */
  bool isInterleave(string s1, string s2, string s3) {
    int length1 = s1.size(), length2 = s2.size(), length3 = s3.size();
    if (length1 + length2 != length3) return false;
    bool dp[length1 + 1][length2 + 1];
    for (int i = 0; i < length1; i++)
      for (int j = 0; j < length2; j++)
        dp[i][j] = false;
    dp[0][0] = true;
    for (int i = 1; i <= length1; i++)
      dp[i][0] = (dp[i - 1][0] && s1[i - 1] == s3[i - 1]);
    for (int j = 1; j <= length2; j++)
      dp[0][j] = (dp[0][j - 1] && s2[j - 1] == s3[j - 1]);
    for (int i = 1; i <= length1; i++)
      for (int j = 1; j <= length2; j++)
        dp[i][j] = ((dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]));
    return dp[length1][length2];
  }
};

int main () {
  Solution s;
  cout << boolalpha << s.isInterleave("", "a", "c") << endl;


  // Sudoku-------------
  // vector<vector<char> > board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
  //   {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
  //   {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
  //   {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
  //   {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
  //   {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
  //   {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
  //   {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
  //   {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  // s.printBoard(board);
  // s.solveSudoku(board);
  // s.printBoard(board);
}