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
};

int main() {
  vector<int> nums = {1, 5, 1};
  Solution s;
  cout << s.longestValidParentheses("(()())") << endl;
  return 0;
}
