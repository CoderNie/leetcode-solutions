#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
  void quickSort(vector<vector<int>>& map, int start, int end) {
    if (start >= end) {
      return;
    } else {
      int i = start, j = end;
      vector<int> temp = map[start];
      while (i != j) {
        while (map[j][1] < temp[1] && i < j)
          j--;
        map[i] = map[j];
        while (map[i][1] >= temp[1] && i < j)
          i++;
        map[j] = map[i];
      }
      map[i] = temp;
      quickSort(map, start, i - 1);
      quickSort(map, i + 1, end);
    }
  }
  vector<int> topKFrequent(vector<int>& nums, int k) {
    vector<vector<int>> map;
    for (int i = 0; i < nums.size(); i++) {
      bool flag = true;
      for (int j = 0; j < map.size(); j++) {
        if (map[j][0] == nums[i]) {
          map[j][1]++;
          flag = false;
          break;
        }
      }
      if (flag) {
        map.push_back({nums[i], 1});
      }
    }
    quickSort(map, 0, map.size() - 1);
    vector<int> result;
    for (int i = 0; i < k; i++) {
      result.push_back(map[i][0]);
    }
    return result;
  }
};

int main () {
  vector<int> arr = {4,1,-1,2,-1,2,3};
  Solution solution;
  arr = solution.topKFrequent(arr, 2);
  for (int i = 0; i < arr.size(); i++) {
    cout << arr[i] << "\t";
  }
  cout << endl;
}