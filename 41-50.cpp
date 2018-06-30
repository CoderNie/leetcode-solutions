#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <stack>

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
  // 48. Rotate Image
  /*
    i,j    j,n-1-i    n-1-i, n-1-j  n-1-j,i
  */
  void rotate(vector<vector<int> >& matrix) {
    int n = matrix.size(), temp;
    for (int i = 0; i < n / 2; i++) {
      for (int j = 0; j < (n + 1) / 2; j++) {
        cout << matrix[i][j] << "\t" << matrix[j][n-1-i] << "\t" << matrix[n-1-i][n-1-j] << "\t" << matrix[n-1-j][i] << endl;
        temp = matrix[i][j];
        matrix[i][j] = matrix[n-1-j][i];
        matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
        matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
        matrix[j][n-1-i] = temp;
      }
    }        
  }
  // 49. Group Anagrams
  vector<vector<string> > groupAnagrams(vector<string>& strs) {
    vector<map<char, int> > maps;
    vector<vector<string> > result;
    map<char, int>::iterator iter;
    for (string str : strs) {
      map<char, int> newMap;
      for (char c : str) {
        if (newMap.find(c) == newMap.end()) {
          newMap[c] = 1;
        } else {
          newMap[c]++;
        }
      }
      int targetIndex = -1;
      for (int i = 0; i < maps.size(); i++) {
        bool isEqual = true;
        if (newMap.size() != maps[i].size()) continue;
        for(iter = maps[i].begin(); iter != maps[i].end(); iter++) {
          if (newMap.find(iter->first) == newMap.end() || newMap[iter->first] != iter->second) {
            isEqual = false;
            break;
          }
        }
        if (isEqual) {
          targetIndex = i;
          break;
        }
      }
      if (targetIndex != -1) {
        result[targetIndex].push_back(str);
      } else {
        result.push_back({str});
        maps.push_back(newMap);
      }
    }
    return result;
  }
  // 50. Pow(x, n)
  double myPow(double x, int n) {
    bool isNeg = false;
    long ln = n;
    if (ln < 0) {
      isNeg = true;
      ln *= -1;
    }
    stack<bool> mark;
    while (ln > 0) {
      mark.push(ln % 2 == 1);
      ln /= 2;
    }
    double result = 1;
    while (!mark.empty())  {
      if(mark.top()) result *= x;
      mark.pop();
      if (!mark.empty()) result *= result;
    }
    return isNeg ? 1/result : result;
  }
};

int main() {
  Solution s;
  cout << pow(2, INT32_MIN) << endl;
  cout << s.myPow(2, INT32_MIN) << endl;
  // s.myPow(0.2, 13);
  return 0;
}