#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
  bool isMatch(string s, string p) {
    int n = s.size();
    int m = p.size();
    // initial
    bool dp[n + 1][m + 1];
    for (int i = 0; i < n + 1; i++) {
      for (int j = 0; j < m + 1; j++) {
        dp[i][j] = false;
      }
    }
    // start
    dp[0][0] = true;
    for (int i = 1; i < n + 1; i++) {
      dp[i][0] = false;
    }
    for (int j = 1; j < m + 1; j++) {
      if (j % 2 == 0) {
        dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
      } else {
        dp[0][j] = false;
      }
    }
    // trans
    bool compare;
    for (int i = 1; i < n + 1; i++) {
      for (int j = 1; j < m + 1; j++) {
        if (p[j - 1] != '*') {
          dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
        } else {
          compare = (s[i - 1] == p[j - 2] || p[j - 2] == '.');
          dp[i][j] = dp[i][j - 2] || (dp[i - 1][j - 2] && compare) || (dp[i - 1][j] && compare);
        }
      }
    }
    return dp[n][m];
  }
};

int main () {
  Solution solution;
  string s, p;
  while (cin >> s >> p) {
    cout << boolalpha << solution.isMatch(s, p) << endl;
  }
}