#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  void quickSort(vector<int> & nums, int start, int end){ 
    if (start >= end) {
      return;
    } else {
      int i = start, j = end;
      int temp = nums[start];
      while (i != j) {
        while (i < j && nums[j] <= temp)
          j--;
        nums[i] = nums[j];
        while (i < j && nums[i] >= temp)
          i++;
        nums[j] = nums[i];
      }
      nums[i] = temp;
      quickSort(nums, start, i - 1);
      quickSort(nums, i + 1, end);
    }
  }
  bool dfs (vector<int>& nums, vector<bool>& flags, int value, int pattern, int size, int nowLength) {
    if (nowLength == nums.size()) {
      if (value == 0) {
        return true;
      } else {
        return false;
      }
    }
    for (int i = 0; i < flags.size(); i++) {
      if (flags[i] == false) {
        int nextValue = nums[i] + value;
        if (nextValue > pattern) {
          continue;
        } else {
          flags[i] = true;
          if (nextValue == pattern) {
            nextValue = 0;
          }
          if (dfs(nums, flags, nextValue, pattern, size, nowLength + 1)){
            return true;
          } else {
            flags[i] = false;
          }
        }
      }
    }
    return false;
  }
  // 473. Matchsticks to Square
  bool makesquare(vector<int>& nums) {
    int sum = 0;
    vector<bool> flags;
    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
      flags.push_back(false);
    }
    quickSort(nums, 0, nums.size() - 1);
    if (sum == 0) {
      return false;
    } else {
      if (sum % 4 != 0) {
        return false;
      } else {
        int value = nums[0];
        if (value > sum / 4) {
          return false;
        } else {
          flags[0] = true;
          value = nums[0] % (sum / 4);
          return dfs(nums, flags, value, sum / 4, nums.size(), 1);
        }
      }
    }
  }
};

int main () {
  // vector<int> nums = {5,5,5,5,16,4,4,4,4,4,3,3,3,3,4};
  vector<int> nums = {};

  // for (int i = 0; i < nums.size(); i++)
  //   cout << nums[i] << " ";
  // cout << endl;
  // cout << nums.size() << endl;
  Solution solution;
  cout << boolalpha << solution.makesquare(nums) << endl;
}