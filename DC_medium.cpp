#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  void quickSort(vector<int>& vint, int start, int end, int k) {
    if (start >= end) {
      return;
    } else {
      int i = start, j = end, temp = vint[start];
      while (i != j) {
        while (vint[j] <= temp && i < j)
          j--;
        if (j > i) 
          vint[i] = vint[j];
        while (vint[i] >= temp && i < j)
          i++;
        if (j > i)
          vint[j] = vint[i];
      }
      vint[i] = temp;
      if (k - 1 == i) {
        return;
      } else if (k - 1 < i) {
        quickSort(vint, start, i - 1, k);
      } else {
        quickSort(vint, i + 1, end, k);
      }
    }
  }

  int findKthLargest(vector<int>& nums, int k) {
    quickSort(nums, 0, nums.size() - 1, k);
    return nums[k - 1];
  }

  // 240. Search a 2D Matrix II
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
      return false;
    }
    int i = 0, j = matrix[0].size() - 1;
    while (i <= matrix.size() - 1 && j >= 0) {
      if (matrix[i][j] > target) {
        j--;
      } else if (matrix[i][j] < target) {
        i++;
      } else {
        return true;
      }
    }
    return false;
  }
};

int main() {
  vector<vector<int>> arr = {{3,3,8,13,13,18},{4,5,11,13,18,20},{9,9,14,15,23,23},{13,18,22,22,25,27},{18,22,23,28,30,33},{21,25,28,30,35,35},{24,25,33,36,37,40}};
  Solution solution;
  cout << boolalpha << solution.searchMatrix(arr, 21) << endl;

  return 0;
}