#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  // 2. Add Two Numbers
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *head = NULL, *p;
    int carry = 0, sum;
    while (l1 != NULL || l2 != NULL || carry != 0) {
      sum = 0;
      if (l1 != NULL) {
        sum += l1->val;
        l1 = l1->next;
      }
      if (l2 != NULL) {
        sum += l2->val;
        l2 = l2->next;
      }
      sum += carry;
      carry = sum / 10;
      sum %= 10;
      ListNode *newNode = new ListNode(sum);
      if (head == NULL) {
        head = newNode;
        p = newNode;
      } else {
        p->next = newNode;   
        p = p->next;
      }
    }
    return head;
  }

  // 1. Two Sum
  vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> myMap;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
      if (myMap.find(target - nums[i]) == myMap.end()) {
        myMap[nums[i]] = i;
      } else {
        result = {myMap[target - nums[i]], i};
        break;
      }
    }
    return result;
  }

  // 3. Longest Substring Without Repeating Characters
  int lengthOfLongestSubstring_bruteForce(string s) {
    int res = 0, sum;
    for (int i = s.size() - 1; i >= 0; i--) {
      sum = 1;
      for (int j = i - 1; j >= 0; j--) {
        bool flag = true;
        for (int k = i; k > j; k--) {
          if (s[j] == s[k]) {
            flag = false;
            break;
          }
        }
        if (flag) {
          sum++;
        } else {
          break;
        }
      }
      res = max(res, sum);
    }
    return res;      
  }
  int lengthOfLongestSubstring(string s) {
    map<char, int> myMap;
    int res = 0;
    for (int i = 0, j = 0; j < s.size(); j++){
      if (myMap.find(s[j]) != myMap.end()) {
        i = max(i, myMap[s[j]] + 1);
      }
      myMap[s[j]] = j;
      res = max(res, j - i + 1);
    }
    return res;
  }

  // 4. Median of Two Sorted Arrays
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    if (m > n) {
      vector<int> temp = nums1;
      nums1 = nums2;
      nums2 = temp;
      m = m + n;
      n = m - n;
      m = m - n;
    }
    if (m == 0) {
      if (n == 0) {
        return 0;
      } else {
        if (n % 2 == 1) {
          return nums2[n / 2];
        } else {
          return (double)(nums2[n / 2] + nums2[n / 2 - 1]) / 2;
        }
      }
    }
    int iMin = 0, iMax = m, sizeSum = (m + n + 1) / 2, i, j;
    while (iMin <= iMax) {
      i = (iMax + iMin) / 2;
      j = sizeSum - i;
      if (nums2[j - 1] > nums1[i] && i < iMax) {
        iMin = i + 1;
      } else if (nums1[i - 1] > nums2[j] && i > iMin) {
        iMax = i - 1;
      } else {
        int maxLeft, minRight;
        if (i == 0) {
          maxLeft = nums2[j - 1];
        } else if (j == 0) {
          maxLeft = nums1[i - 1];
        } else {
          maxLeft = max(nums1[i - 1], nums2[j - 1]);
        }
        if ((m + n) % 2 == 1) {
          return maxLeft;
        }
        if (i == m) {
          minRight = nums2[j];
        } else if (j == n) {
          minRight = nums1[i];
        } else {
          minRight = min(nums1[i], nums2[j]);
        }
        return (double)(maxLeft + minRight) / 2;
      }
    }
    return 0;
  }

  // 5. Longest Palindromic Substring
  string longestPalindrome(string s) {
    int length = s.size();
    if (length == 0) return s;
    int resI = 0, resJ = 0;
    bool dp[length + 1][length + 1];
    for (int i = 0; i <= length; i++)
      dp[i][i] = true;
    for (int i = 0; i < length; i++) {
      if (s[i] == s[i + 1]) {
        dp[i][i + 1] = true;
        if (resJ - resI < 1) {
          resI = i;
          resJ = i + 1;
        }
      } else {
        dp[i][i + 1] = false;
      }
    }
    for (int gap = 2; gap < length; gap++) {
      for (int i = 0; i + gap < length; i++) {
        int j = i + gap;
        if (s[i] == s[j] && dp[i + 1][j - 1]) {
          dp[i][j] = true;
          if (resJ - resI < j - i) {
            resI = i;
            resJ = j;
          }
        } else {
          dp[i][j] = false;
        }
      }
    }
    return s.substr(resI, resJ - resI + 1);
  }

  // 6. ZigZag Conversion
  string convert(string s, int numRows) {
    if (numRows == 1) return s;
    string res;
    bool shouldIncrease = true;
    string strArr[numRows];
    int point = 0;
    for (char c : s) {
      strArr[point] += c;
      if (point == numRows - 1) {
        shouldIncrease = false;
      } else if (point == 0) {
        shouldIncrease = true;
      }
      if (shouldIncrease) {
        point++;
      } else {
        point--;
      }
    }
    for (string str: strArr) {
      res += str;
    }
    return res;
  }

  // 7. Reverse Integer
  int reverse(int x) {
    long result = 0, longX = abs((long)x);
    while (longX > 0) {
      result = result * 10 + longX % 10;
      longX /= 10;
    }
    result = (x > 0) ? result : -result;
    if (result > INT32_MAX || result < INT32_MIN) {
      return 0;
    } else {
      return (int)result;
    }
  }

  // 8. String to Integer (atoi)
  int myAtoi(string str) {
    long result = 0;
    bool isInit = false;
    bool isNeg = false;
    for (char c : str) {
      if (c == ' ') {
        if (isInit) {
          break;
        } else {
          continue;
        }
      } else if (c == '-' || c == '+') {
        if (!isInit) {
          isInit = true;
        } else {
          break;
        }
        isNeg = (c == '-');
      } else if (c >= 48 && c <= 57) {
        isInit = true;
        result = result * 10 + (c - 48);
        if (result > INT32_MAX) { 
          return isNeg ? INT32_MIN : INT32_MAX;
        }
      } else {
        break;
      }
    }      
    return (int)(isNeg ? -result : result);
  }

  // 9. Palindrome Number
  bool isPalindrome(int x) {
    if (x < 0) {
      return false;
    } else {
      return (x == reverse(x));
    }
  }
  
  // 10. Regular Expression Matching
  bool isMatch(string s, string p) {
    int n = s.size();
    int m = p.size();
    // initial
    bool dp[n + 1][m + 1];
    for (int i = 0; i < n + 1; i++) {
      for (int j = 0; j < m + 1; j++) {
        dp[i][j] = false;
      }
    }
    // start
    dp[0][0] = true;
    for (int i = 1; i < n + 1; i++) {
      dp[i][0] = false;
    }
    for (int j = 1; j < m + 1; j++) {
      if (j % 2 == 0) {
        dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
      } else {
        dp[0][j] = false;
      }
    }
    // trans
    bool compare;
    for (int i = 1; i < n + 1; i++) {
      for (int j = 1; j < m + 1; j++) {
        if (p[j - 1] != '*') {
          dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
        } else {
          compare = (s[i - 1] == p[j - 2] || p[j - 2] == '.');
          dp[i][j] = dp[i][j - 2] || (dp[i - 1][j - 2] && compare) || (dp[i - 1][j] && compare);
        }
      }
    }
    return dp[n][m];
  }

};

int main () {
  Solution s;
  vector<int> nums1 = {3, 3};
  vector<int> nums2 = {};
  cout << s.findMedianSortedArrays(nums1, nums2) << endl;
  return 0;
}