#include <map>
#include <queue>
#include <stack>
#include <set>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  // 11. Container With Most Water
  int maxArea(vector<int>& height) {
    int res = 0, i = 0, j = height.size() - 1;
    while (i != j) {
      res = max(res, (j - i) * min(height[i], height[j]));
      if (height[i] > height[j]) {
        j--;
      } else {
        i++;
      }
    }
    return res;
  }
  // 12. Integer to Roman
  string intToRoman(int num) {
    map<int, char> romanMap;
    romanMap[1] = 'I';
    romanMap[5] = 'V';
    romanMap[10] = 'X';
    romanMap[50] = 'L';
    romanMap[100] = 'C';
    romanMap[500] = 'D';
    romanMap[1000] = 'M';
    string res;
    for (int i = 3; i >= 0; i--) {
      int fold = pow(10, i);
      if (num / fold == 9) {
        res += romanMap[fold];
        res += romanMap[fold * 10];
      } else if (num / fold == 4) {
        res += romanMap[fold];
        res += romanMap[fold * 5];
      } else if (num / fold > 0) {
        if (num / fold >= 5) {
          res += romanMap[fold * 5];
          num -= 5 * fold;
        }
        for (int i = 0; i < num / fold; i++) {
          res += romanMap[fold];
        }
      }
      num %= fold;
    }
    return res;
  }
  // 13. Roman to Integer
  int romanToInt (string s) {
    int res = 0;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == 'I') {
        res += 1;
      } else if (s[i] == 'V') {
        res += 5;
        if (i - 1 >= 0 && s[i - 1] == 'I') {
          res -= 2;
        }
      } else if (s[i] == 'X') {
        res += 10;
        if (i - 1 >= 0 && s[i - 1] == 'I') {
          res -= 2;
        }
      } else if (s[i] == 'L') {
        res += 50;
        if (i - 1 >= 0 && s[i - 1] == 'X') {
          res -= 20;
        }
      } else if (s[i] == 'C') {
        res += 100;
        if (i - 1 >= 0 && s[i - 1] == 'X') {
          res -= 20;
        }
      } else if (s[i] == 'D') {
        res += 500;
        if (i - 1 >= 0 && s[i - 1] == 'C') {
          res -= 200;
        }
      } else if (s[i] == 'M') {
        res += 1000;
        if (i - 1 >= 0 && s[i - 1] == 'C') {
          res -= 200;
        }
      }
    }
    return res;
  }
  // 14. Longest Common Prefix
  string longestCommonPrefix(vector<string>& strs) {
    if (strs.size() == 0) return "";
    int length = 0;
    while (true) {
      if (strs[0].size() < length + 1) break;
      for (int i = 0; i < strs.size() - 1; i++)
        if (strs[i + 1].size() < length + 1 || strs[i][length] != strs[i + 1][length])
          return strs[0].substr(0, length);
      length++;
    }
    return strs[0].substr(0, length);
  }
  // 15. 3Sum
  vector<vector<int> > threeSum(vector<int>& nums) {
    vector<vector<int> > res;
    if (nums.size() < 3) return res;
    sort(nums.begin(), nums.end());
    int p, q, sum;
    for (int i = 0; i < nums.size() - 2; i++) {
      if (nums[i] > 0) 
        break;
      else if (i > 0 && nums[i] == nums[i - 1]) 
        continue;
      p = i + 1;
      q = nums.size() - 1;
      while (p < q) {
        sum = nums[i] + nums[p] + nums[q];
        if (sum == 0) {
          res.push_back({nums[i], nums[p], nums[q]});
          while (nums[p] == nums[p + 1] && p < q)
            p++;
          p++;
          while (nums[q] == nums[q - 1] && p < q)
            q--;
          q--;
        } else if (sum > 0) {
          while (nums[q] == nums[q - 1] && p < q)
            q--;
          q--;
        } else {
          while (nums[p] == nums[p + 1] && p < q)
            p++;
          p++;
        }
      }
    }
    return res;
  }

  // 16. 3Sum Closest
  int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int p, q, sum;
    int gap = INT_MAX;
    int res;
    for (int i = 0; i < nums.size() - 2; i++) {
      if (i > 0 && nums[i] == nums[i - 1]) continue;
      p = i + 1;
      q = nums.size() - 1;
      while (p < q) {
        sum = nums[i] + nums[p] + nums[q];
        if (sum == target) {
          return target;
        } else if (sum > target) {
          if (sum - target < gap) {
            gap = sum - target;
            res = sum;
          }
          while (nums[q] == nums[q - 1] && p < q)
            q--;
          q--;
        } else {
          if (target - sum < gap) {
            gap = target - sum;
            res = sum;
          }
          while (nums[p] == nums[p + 1] && p < q)
            p++;
          p++;
        }
      }
    }
    return res;
  }
  

  // 17. Letter Combinations of a Phone Number
  vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) return {};
    map<int, string> digitalMap;
    digitalMap[2] = "abc";
    digitalMap[3] = "def";
    digitalMap[4] = "ghi";
    digitalMap[5] = "jkl";
    digitalMap[6] = "mno";
    digitalMap[7] = "pqrs";
    digitalMap[8] = "tuv";
    digitalMap[9] = "wxyz";
    vector<string> linshi;
    vector<string> res = {""};
    for (int i = 0; i < digits.size(); i++) {
      string tails = digitalMap[digits[i] - 48];
      for (int j = 0; j < res.size(); j++) {
        for (int n = 0; n < tails.size(); n++) {
          linshi.push_back(res[j] + tails[n]);
        }
      }
      res = linshi;
      linshi = {};
    }
    return res;
  }

  // 18. 4Sum 
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > res;
    if (nums.size() < 4) return res;
    sort(nums.begin(), nums.end());
    int p, q, sum;
    for (int j = 0; j < nums.size() - 3; j++) {
      if (j > 0 && nums[j] == nums[j - 1])
        continue;
      int target3 = target - nums[j];  
      for (int i = j + 1; i < nums.size() - 2; i++) {
        if (i > j + 1 && nums[i] == nums[i - 1]) 
          continue;
        p = i + 1;
        q = nums.size() - 1;
        while (p < q) {
          sum = nums[i] + nums[p] + nums[q];
          if (sum == target3) {
            res.push_back({nums[j], nums[i], nums[p], nums[q]});
            while (nums[p] == nums[p + 1] && p < q)
              p++;
            p++;
            while (nums[q] == nums[q - 1] && p < q)
              q--;
            q--;
          } else if (sum > target3) {
            while (nums[q] == nums[q - 1] && p < q)
              q--;
            q--;
          } else {
            while (nums[p] == nums[p + 1] && p < q)
              p++;
            p++;
          }
        }
      }
    }
    return res;
  }

  // 19. Remove Nth Node From End of List
  ListNode* removeNthFromEnd_h(ListNode* head, int n) {
    ListNode* p = head;
    vector<ListNode*> nodeList;
    while (p->next != NULL) {
      nodeList.push_back(p);
      p = p->next;
    }
    nodeList.push_back(p);
    if (nodeList.size() == n) {
      return nodeList[1];
    } else {
      if (n == 1) {
        nodeList[nodeList.size() - 2]->next = NULL;
      } else {
        nodeList[nodeList.size() - n - 1]->next = nodeList[nodeList.size() - n + 1];
      }
      return nodeList[0];
    }
  }
  // 19. Remove Nth Node From End of List
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode *p = dummy, *q = dummy;
    for (int i = 0; i <= n; i++)
      p = p->next;
    while (p != NULL) {
      p = p->next;
      q = q->next;
    }
    q->next = q->next->next;
    return dummy->next;
  }
  // 20. Valid Parentheses
  bool isValid(string s) {
    stack<char> brackets;
    map<char, char> bracketMap;
    bracketMap[')'] = '(';
    bracketMap[']'] = '[';
    bracketMap['}'] = '{';
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
        brackets.push(s[i]);
      } else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
        if (!brackets.empty() && brackets.top() == bracketMap[s[i]]) {
          brackets.pop();
        } else {
          return false;
        }
      }
    }
    if (brackets.empty()) return true;
    else return false;
  }
};

int main () {
  Solution s;
  vector<int> res = {0, 0, 0};
  vector<vector<int> > output = s.threeSum(res);
  cout << output.size() << endl;

}