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
struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
  // 54. Spiral Matrix
  vector<int> spiralOrder(vector<vector<int> >& matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) return {};
    int m = matrix.size(), n = matrix[0].size();
    int paceInfo[4][3] = {
      {0, 1, n},
      {1, 0, m - 1},
      {0, -1, n - 1},
      {-1, 0, m - 2}
    };
    vector<int> result;
    int p = 0, q = -1, count = 0, nowPath = 0;
    while (count < m * n) {
      if (paceInfo[nowPath][2] > 0) {
        for (int i = 0; i < paceInfo[nowPath][2]; i++) {
          p += paceInfo[nowPath][0];
          q += paceInfo[nowPath][1];
          result.push_back(matrix[p][q]);
          count++;
        }
        paceInfo[nowPath][2] -= 2;
      }
      nowPath = (nowPath + 1) % 4;
    }
    return result;
  }
  // 55. Jump Game
  bool canJump(vector<int>& nums) {
    int lastPos = nums.size() - 1;
    for (int i = lastPos - 1; i >= 0; i--)
      if (i + nums[i] >= lastPos)
        lastPos = i;
    return lastPos <= 0;
  }
  // 56. Merge Intervals
  static bool comparison(Interval a,Interval b){
    return a.start<b.start;
  }
  vector<Interval> merge(vector<Interval>& intervals) {
    if (intervals.size() <= 1) return intervals;
    sort(intervals.begin(), intervals.end(), comparison);
    vector<Interval> results;
    results.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); i++) {
      auto p = intervals[i];
      auto &q = results.back();
      if (max(p.start, q.start) <= min(p.end, q.end)) {
        q.start = min(p.start, q.start);
        q.end = max(p.end, q.end);
      } else {
        results.push_back(p);
      }
    }
    return results;        
  }
  // 58. Length of Last Word
  int lengthOfLastWord(string s) {
    int result = 0;
    for (int i = s.size() - 1; i >= 0; i--)
      if (s[i] != ' ') result++;
      else if (result != 0) break;
    return result;
  }
  // 59. Spiral Matrix II
  vector<vector<int> > generateMatrix(int n) {
    int paceInfo[4][3] = {
      {0, 1, n},
      {1, 0, n - 1},
      {0, -1, n - 1},
      {-1, 0, n - 2}
    };
    vector<vector<int> > result(n, vector<int>(n, 0));
    int i = 0, j = -1, nowPath = 0, count = 1;
    while (count <= n * n) {
      for (int k = 0; k < paceInfo[nowPath][2]; k++) {
        i += paceInfo[nowPath][0];
        j += paceInfo[nowPath][1];
        result[i][j] = count++;
      }
      paceInfo[nowPath][2] -= 2;
      nowPath = (nowPath + 1) % 4;
    }
    return result;
  }
  // 60. Permutation Sequence
  string recur(vector<int> & arr, int k) {
    if (arr.size() == 1) return to_string(arr[0]);
    int subSize = 1, i = arr.size() - 1;
    while (i >= 2) subSize *= i--;
    int pos = (k - 1) / subSize;
    vector<int> newArr = arr;
    newArr.erase(newArr.begin() + pos);
    return to_string(arr[pos]) + recur(newArr, k - pos * subSize);
  }
  string getPermutation(int n, int k) {
    vector<int> arr;
    for (int i = 1; i <= n; i++)
      arr.push_back(i);
    return recur(arr, k);
  }
};

int main () {
  vector<int > matrix = {1, 2, 3};
  Solution s;
  cout << s.getPermutation(2, 1) << endl;
  return 0;
}