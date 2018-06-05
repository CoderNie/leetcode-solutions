#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Solution
{
  // 5. Longest Palindromic Substring
public:
  /* 
      Trans: 
        A[i][j] = A[i + 1][j - 1] && (s[i] == s[j])  (i < j)
      Start: 
        A[k][k] = 1
        A[k][k + 1] = (s[k] == s[k + 1])
    */
  string longestPalindrome(string s)
  {
    int n = s.size();
    bool A[n][n];
    int max = 0, start = 0, end = 0;
    // Start:
    for (int i = 0; i < n - 1; i++)
    {
      A[i][i] = true;
      if (s[i] == s[i + 1])
      {
        A[i][i + 1] = true;
        if (1 > max)
        {
          max = 1;
          start = i;
          end = i + 1;
        }
      }
      else
      {
        A[i][i + 1] = false;
      }
    }
    A[n - 1][n - 1] = true;
    // Trans:
    for (int gap = 2; gap < n; gap++)
    {
      for (int i = 0; i < n - gap; i++)
      {
        if (A[i + 1][i + gap - 1] && (s[i] == s[i + gap]))
        {
          A[i][i + gap] = true;
          if (gap > max)
          {
            max = gap;
            start = i;
            end = i + gap;
          }
        }
        else
        {
          A[i][i + gap] = false;
        }
      }
    }
    return s.substr(start, max + 1);
  }

  // 837. New 21 Game
  double new21Game(int N, int K, int W) {
    double dp[K + W];
    double bottom = 0, top = 0, averP = 1.0 / (double)W, lastSum = 1.0;
    if (K == 0) {
      return 1;
    }
    dp[0] = 1.0;
    for (int i = 1; i <= K + W - 1; i++) {
      dp[i] = lastSum * averP;
      if (i < K) lastSum += dp[i];
      if (i - W >= 0) lastSum -= dp[i - W];
    }
    for (int i = K; i <= K + W - 1; i++) {
      bottom += dp[i];
    }
    for (int i = K; i <= N; i++) {
      top += dp[i];
    }
    if (bottom == 0) {
      return 1;
    } else {
      return top / bottom;
    }
  }

  double new21GameOld(int N, int K, int W) {
    double dp[K + W];
    double bottom = 0, top = 0, averP = 1.0 / (double)W;
    if (K == 0) {
      return 1;
    }
    for (int i = 1; i <= W; i++) {
      dp[i] = 1;
    }
    for (int i = W + 1; i <= K + W - 1; i++) {
      dp[i] = 0;
    }
    for (int i = 1; i <= K + W - 1; i++) {
      for (int j = 1; j < i; j++) {
        if (i == 11) {
          cout << i - j << endl;
        }
        if (i - j < K && j <= W) {
          dp[i] += dp[i - j];
        } 
      }
      dp[i] *= averP;
      // cout << "dp[" << i << "] = " << dp[i] << endl;
    }
    for (int i = K; i <= K + W - 1; i++) {
      bottom += dp[i];
    }
    for (int i = K; i <= N; i++) {
      top += dp[i];
    }
    if (bottom == 0) {
      return 1;
    } else {
      return top / bottom;
    }
  }
};

int main()
{
  Solution solution;
  clock_t start = clock();
  cout << solution.new21Game(21, 17, 10) << endl;
  clock_t finish = clock();
  cout << ((double)(finish - start) / CLOCKS_PER_SEC * 1000) << "ms" << endl;
  return 0;
}