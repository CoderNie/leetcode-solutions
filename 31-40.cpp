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

class Solution {
public:
  // 31.
  void nextPermutation(vector<int>& nums) {
    int length = nums.size();
    if (length <= 1) return;
    int mark = -1, markTrans = length - 1;
    for (int i = length - 2; i >= 0; i--) {
      if (nums[i] < nums[i + 1]) {
        mark = i;
        break;
      }
    }
    if (mark != -1) {
      for (int i = mark + 1; i < length; i++) {
        if (nums[i] <= nums[mark]) {
          markTrans = i - 1;
          break;
        }
      }
      int temp = nums[mark];
      nums[mark] = nums[markTrans];
      nums[markTrans] = temp;
    }
    reverse(nums.begin() + mark + 1, nums.end());
  }

  // 32.
  int longestValidParentheses_old(string s) {
    int length = s.size();
    if (length <= 1) return 0;
    int res = 0;
    bool dp[length][length];
    cout << length << endl;
    for (int i = 0; i < length; i++)
      for (int j = 0; j < length; j++)
        dp[i][j] = false;
    for (int i = 0; i < length - 1; i++) {
      if (s[i] == '(' && s[i + 1] == ')') {
        dp[i][i + 1] = true;
        res = 2;
      }
    }
    for (int gap = 3; gap < length - 1; gap += 2) {
      for (int i = 0; i + gap < length; i++) {
        int j = i + gap;
        dp[i][j] = (dp[i + 2][j] && s[i] == '(' && s[i + 1] == ')')
          || (dp[i][j - 2] && s[j] == ')' && s[j - 1] == '(')
          || (dp[i + 1][j - 1] && s[i] == '(' && s[j] == ')');
        if (dp[i][j] && gap + 1 > res) res = gap + 1;
      }
    }
    return res;
  }
  // 32.
  int longestValidParentheses(string s) {
    int length = s.size();
    if (length <= 1) return 0;
    int dp[length];
    for (int i = 0; i < length; i++) dp[i] = 0;
    int res = 0;
    for (int i = 1; i < length; i++) {
      if (s[i] == ')') {
        if (s[i - 1] == '(') {
          dp[i] = (i - 2 >= 0 ? dp[i - 2] : 0) + 2;
          if (dp[i] > res) res = dp[i];
        } else {
          if (s[i - dp[i - 1] - 1] == '(') {
            dp[i] = dp[i - 1] + 2 + ((i - dp[i - 1] - 2 >= 0) ? dp[i - dp[i - 1] - 2] : 0);
          if (dp[i] > res) res = dp[i];
          }
        }
      }
    }
    return res;
  }
  // 33. Search in Rotated Sorted Array
  int search(vector<int>& nums, int target) {
    int length = nums.size(), start = 0, end = length - 1, mid;
    if (length == 0) return -1;
    while (start <= end) {
      // cout << start << "\t" << end << endl;
      mid = (start + end) / 2;
      if (nums[start] < nums[end]) {
        if (target == nums[mid]) {
          return mid;
        } else if (target > nums[mid]) {
          start = mid + 1;
        } else {
          end = mid - 1;
        }
      } else {
        if (nums[mid] > nums[start]) {
          if (target > nums[mid]) {
            start = mid + 1;
          } else if (target == nums[mid]) {
            return mid;
          } else if (target > nums[start]) {
            end = mid - 1;
          } else if (target == nums[start]) {
            return start;
          } else if (target > nums[end]) {
            end = mid - 1;
          } else if (target == nums[end]) {
            return end;
          } else {
            start = mid + 1;
          }
        } else {
          if (target > nums[start]) {
            end = mid - 1;
          } else if (target == nums[start]) {
            return start;
          } else if (target > nums[end]) {
            return -1;
          } else if (target == nums[end]) {
            return end;
          } else if (target > nums[mid]) {
            start = mid + 1;
          } else if (target == nums[mid]) {
            return mid;
          } else {
            end = mid - 1;
          }
        }
      }
    }
    return -1;
  }
  // 34. Search for a Range
  vector<int> searchRange(vector<int>& nums, int target) {
    int length = nums.size(), start, end, mid, resLeft = -1, resRight = -1;
    if (length == 0) return {-1, -1};
    start = 0, end = length - 1;
    while (start < end) {
      mid = (start + end) / 2;
      if (nums[mid] >= target) {
        end = mid;
      } else {
        start = mid + 1;
      }
    }
    if (nums[start] == target) resLeft = start;
    start = 0, end = length - 1;
    while (start < end) {
      mid = (start + end + 1) / 2;
      if (nums[mid] > target) {
        end = mid - 1;
      } else {
        start = mid;
      }
    }
    if (nums[start] == target) resRight = start;
    return {resLeft, resRight};
  }
  // 36. Valid Soduku
  bool isValidSudoku(vector<vector<char>>& board) {
    int a, temp;
    for (int i = 0; i < 9; i++){
      a = 0;
      for (int j = 0; j < 9; j++) {
        if (board[i][j] != '.') {
          temp = board[i][j] - 48;
          if ((a >> temp) % 2 == 0) {
            a += (2 << (temp - 1));
          } else {
            return false;
          }
        }
      }
      a = 0;
      for (int j = 0; j < 9; j++) {
        if (board[j][i] != '.') {
          temp = board[j][i] - 48;
          if ((a >> temp) % 2 == 0) {
            a += (2 << (temp - 1));
          } else {
            return false;
          }
        }
      }
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        a = 0;
        for (int p = 0; p < 3; p++) {
          for (int q = 0; q < 3; q++) {
            if (board[i * 3 + p][j * 3 + q] != '.') {
              temp = board[i * 3 + p][j * 3 + q] - 48;
              if ((a >> temp) % 2 == 0) {
                a += (2 << (temp - 1));
              } else {
                return false;
              }
            }
          }
        }
      }
    }
    return true;        
  }
};

int main() {
  vector<int> nums = {5,7,7,8,8,10};
  Solution s;
  cout << '0' - 48 << endl;
  return 0;
}
