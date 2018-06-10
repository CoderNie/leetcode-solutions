#include <iostream>
#include <queue>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>
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
  // 15. 3Sum
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    set<string> mySet;
    if (nums.size() < 3) return res;
    sort(nums.begin(), nums.end());
    int p, q, sum;
    for (int i = 0; i < nums.size() - 2; i++) {
      p = i + 1;
      q = nums.size() - 1;
      while (p < q) {
        sum = nums[i] + nums[p] + nums[q];
        if (sum == 0) {
          ostringstream fir, sec;
          fir << nums[i];
          sec << nums[p];
          string key = fir.str() + sec.str();
          if (mySet.find(key) == mySet.end()) {
            mySet.insert(key);
            res.push_back({nums[i], nums[p], nums[q]});
          }
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
      while (nums[i] == nums[i + 1])
        i++;
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
      while (nums[i] == nums[i + 1])
        i++;
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
    return {{}};
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

};

int main () {
  Solution s;
  vector<string> res = s.letterCombinations("23");
  cout << res.size() << endl;
  for (string str: res) {
    cout << str << endl;
  }
}