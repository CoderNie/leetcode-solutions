#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
  // 835. Image Overlap -- Complicated
  int largestOverlap1(vector<vector<int>>& A, vector<vector<int>>& B) {
    int length = A.size();
    int max = 0;
    int minLimit = length * -1 + 1;
    int maxLimit = length - 1;
    for (int i = minLimit; i <= maxLimit; i++) {
      for (int j = minLimit; j <= maxLimit; j++) {
        int sum = 0;
        for (int p = 0; p < length; p++) {
          for (int q = 0; q < length; q++) {
            if (B[p][q] == 1 && p - i >= 0 && p - i < length && q - j >= 0 && q - j < length) {
              if (A[p - i][q - j] == 1) {
                sum++; 
              }
            }
          }
        }
        if (sum > max) {
          max = sum;
        }
      }
    }
    return max;
  }
  // 835. Image Overlap -- Better
  int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
    int length = A.size();
    int sum[length * 2][length * 2];
    for (int i = 1; i < length * 2; i++)
      for (int j = 1; j < length * 2; j++)
        sum[i][j] = 0;
    int minLimit = length * -1 + 1;
    int maxLimit = length - 1;
    for (int i = 0; i < length; i++)
      for (int j = 0; j < length; j++)
        if (A[i][j] == 1)
          for (int p = -i; p < length - i; p++)
            for (int q = -j; q < length - j; q++)
              if (B[i + p][j + q] == 1)
                sum[p + length][q + length]++;
    int res = 0;
    for (int i = 1; i < length * 2; i++)
      for (int j = 1; j < length * 2; j++)
        res = max(res, sum[i][j]);
    return res;
  }


  // 840. Magic Squares In Grid
  int numMagicSquaresInside(vector<vector<int>>& grid) {
    int height = grid.size();
    int width = grid[0].size();
    if (height < 3 || width < 3) {
      return 0;
    } else {
      int sum = 0;
      bool flags[9];
      bool flag;
      for (int i = 0; i <= height - 3; i++) {
        for (int j = 0; j <= width - 3; j++) {
          flag = true;
          for (int p = 1; p <= 9; p++)
            flags[p] = false;
          for (int p = 0; p < 3; p++)
            for (int q = 0; q < 3; q++)
              if (grid[p + i][q + j] <= 9 && grid[p + i][q + j] >= 1 && !flags[grid[p + i][q + j]]) {
                flags[grid[p + i][q + j]] = true;
              } else {
                flag = false;
              }
          if (!flag) continue;
          int total_1 = grid[i][j] + grid[i][j + 1] + grid[i][j + 2];
          int total_2 = grid[i + 1][j] + grid[i + 1][j + 1] + grid[i + 1][j + 2];
          if (total_1 == total_2) {
            total_2 = grid[i + 2][j] + grid[i + 2][j + 1] + grid[i + 2][j + 2];
            if (total_1 == total_2) {
              total_2 = grid[i][j] + grid[i + 1][j] + grid[i + 2][j];
              if (total_1 == total_2) {
                total_2 = grid[i][j + 1] + grid[i + 1][j + 1] + grid[i + 2][j + 1];
                if (total_1 == total_2) {
                  total_2 = grid[i][j + 2] + grid[i + 1][j + 2] + grid[i + 2][j + 2];
                  if (total_1 == total_2) {
                    total_2 = grid[i][j] + grid[i + 1][j + 1] + grid[i + 2][j + 2];
                    if (total_1 == total_2) {
                      total_2 = grid[i][j + 2] + grid[i + 1][j + 1] + grid[i + 2][j];
                      if (total_1 == total_2) {
                        sum++;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      return sum;
    }
  }
};

int main () {
  vector<vector<int>> A = {{1,1,0}, {0,1,0}, {0,1,0}};
  vector<vector<int>>B = {{0,0,0},{0,1,1},{0,0,1}};
  Solution s;
  cout << s.largestOverlap(A, B) << endl;
}