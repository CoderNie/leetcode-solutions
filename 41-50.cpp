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
  string add(string num1, string num2) {
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    string result = "";
    int length1 = num1.size(), length2 = num2.size();
    int sum, remain = 0;
    for (int i = 0; i < max(length1, length2); i++) {
      sum = remain;
      if (i < length1) sum += (num1[i] - 48);
      if (i < length2) sum += (num2[i] - 48);
      remain = sum / 10;
      result += (char)(sum % 10 + 48);
    }
    if (remain != 0) result += (char)(remain + 48);
    reverse(result.begin(), result.end());
    return result;
  }

  string multiplySingle(string num1, int num2) {
    if (num2 == 10) {
      return num1 + "0";
    } else if (num2 > 10) {
      return "num2 must be lower than or equal to 10";
    } else {
      reverse(num1.begin(), num1.end());
      int product, remain = 0;
      string result = "";
      for (int i = 0; i < num1.size(); i++) {
        product = (remain + (num1[i] - 48) * num2);
        remain = product / 10;
        result += (char)(product % 10 + 48);
      }
      if (remain != 0) result += (char)(remain + 48);
      reverse(result.begin(), result.end());
      return result;
    }
  }

  void removeZero(string & result) {
    int i = 0;
    while (i + 1 < result.size()) {
      if (result[i] == '0') {
        result.erase(0, 1);
      } else {
        break;
      }
    }
  }

  // 43. Multiply String
  string multiply(string num1, string num2) {
    if (num1.size() < num2.size()) swap(num1, num2);
    string result = "0";
    for (int i = 0; i < num2.size(); i++) {
      result = add(multiplySingle(result, 10), multiplySingle(num1, num2[i] - 48));
    }
    removeZero(result);
    return result;
  }
  // 46. Permutations
  vector<vector<int> > permute(vector<int>& nums) {
    if (nums.size() <= 1) return { nums };
    vector<vector<int> > result = {{ nums[0] }};
    for (int i = 1; i < nums.size(); i++) {
      int tempSize = result.size();
      for (int j = 0; j < tempSize; j++) {
        int nowSize = result[j].size();
        for (int k = 1; k <= nowSize; k++) {
          vector<int> newOne = result[j];
          newOne.insert(newOne.begin() + k, nums[i]);
          result.push_back(newOne);
        }
        result[j].insert(result[j].begin(), nums[i]);
      }
    }
    reverse(result.begin(), result.end());
    for (int i = 0; i < result.size(); i++) {
      for (int j = 0; j < result[i].size(); j++) {
        cout << result[i][j] << "\t";
      }
      cout << endl;
    }
    return result;
  }
  // 47. Permutations 2
  bool isDuplicate(vector<vector<int> > & result, vector<int>& newOne) {
    for (int i = 0; i < result.size(); i++) {
      if (result[i].size() == newOne.size()) {
        bool flag = true;
        for (int j = 0; j < newOne.size(); j++) {
          if (result[i][j] != newOne[j]) {
            flag = false;
            break;
          }
        }
        if (flag) return true;
      }
    }
    return false;
  }
  vector<vector<int> > permuteUnique(vector<int>& nums) {
    if (nums.size() <= 1) return { nums };
    vector<vector<int> > result = {{ nums[0] }}, tempResult;
    for (int i = 1; i < nums.size(); i++) {
      tempResult = result;
      result = {};
      for (int j = 0; j < tempResult.size(); j++) {
        for (int k = 0; k <= tempResult[j].size(); k++) {
          vector<int> newOne = tempResult[j];
          newOne.insert(newOne.begin() + k, nums[i]);
          if (!isDuplicate(result, newOne)) {
            result.push_back(newOne);
          }
        }
      }
    }
    reverse(result.begin(), result.end());
    return result;
  }
};

int main() {
  Solution s;
  vector<int> nums = {};
  cout << s.permuteUnique(nums).size() << endl;
  return 0;
}