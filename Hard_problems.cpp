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
  bool isValueSuitable (vector<vector<char> >& board, int i, int j, char value) {
    for (int k = 0; k < 9; k++) {
      if (board[i][k] == value) return false;
      if (board[k][j] == value) return false;
    }
    int startP = i / 3 * 3, startQ = j / 3 * 3;
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
};

int main () {
  Solution s;
  vector<int> arr = {};
  cout << s.trap(arr) << endl;


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