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

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:  
  // 21. Merge Two Sorted Lists
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* head = new ListNode(0);
    ListNode* p = head;
    while (l1 != NULL && l2 != NULL) {
      if (l1->val < l2 ->val) {
        p->next = l1;
        l1 = l1->next;
      } else {
        p->next = l2;
        l2 = l2->next;
      }
      p = p->next;
    }
    if (l1 != NULL) {
      p->next = l1;
    } else if (l2 != NULL) {
      p->next = l2;
    }
    return head->next;
  }

  // 22. Generate Parentheses O(2^N)
  vector<string> generateParenthesis(int n) {
    if (n == 0) return {};
    // nowString, leftCount, rightCount
    vector<pair<string, pair<int, int> > > res = {{"", {0, 0}}};
    vector<pair<string, pair<int, int> > > linshi;
    for (int i = 0; i < 2 * n; i++) {
      for (int j = 0; j < res.size(); j++) {
        string oldString = res[j].first;
        if (res[j].second.first < n) {
          linshi.push_back({oldString + '(', {res[j].second.first + 1, res[j].second.second}});
        }
        if (res[j].second.first > res[j].second.second) {
          linshi.push_back({oldString + ')', {res[j].second.first, res[j].second.second + 1}});
        }
      }
      res = linshi;
      linshi = {};
    }
    vector<string> result;
    for (int i = 0; i < res.size(); i++) {
      result.push_back(res[i].first);
    }
    return result;
  }

  // 23. Merge k Sorted Lists
  ListNode* mergeKLists_old(vector<ListNode*>& lists) {
    ListNode* dump = new ListNode(0);
    ListNode* p = dump;
    while (true) {
      int min = INT32_MAX;
      int minIndex= -1;
      for (int i = 0; i < lists.size(); i++){
        if (lists[i] != NULL && lists[i]->val < min) {
          min = lists[i]->val;
          minIndex = i;
        }
      }
      if (minIndex != -1) {
        p->next = lists[minIndex];
        p = p->next;
        lists[minIndex] = lists[minIndex]->next;
      } else {
        break;
      }
    }
    return dump->next;
  }

  // 23. Merge k Sorted Lists
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode *dump = new ListNode(0), *p = dump, *nowPoint;
    // val, node
    priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, greater<pair<int, ListNode*>> > pQueue;
    for (ListNode* node : lists) {
      if (node != NULL)
        pQueue.push({node->val, node});
    }
    while (!pQueue.empty()) {
      nowPoint = pQueue.top().second;
      p->next = nowPoint;
      p = p->next;
      pQueue.pop();
      if (nowPoint->next != NULL) {
        pQueue.push({nowPoint->next->val, nowPoint->next});
      }
    }
    return dump->next;
  }

  // 24. Swap Nodes in Pairs
  ListNode* swapPairs(ListNode* head) {
    ListNode *dump = new ListNode(0), *p = dump, *first, *second;
    dump->next = head;
    while (p != NULL && p->next != NULL && p->next->next != NULL) {
      first = p->next;
      second = p->next->next;
      first->next = second->next;
      second->next = first;
      p->next = second;
      p = first;
    }
    return dump->next; 
  }

  // 25. Reverse Nodes in k-Group
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (k == 1) return head;
    vector<ListNode*> nodeList;
    ListNode *dump = new ListNode(0), *p = dump, *former, *latter, *nextLatter, *q;
    dump->next = head;
    while (true) {
      // check count of left nodes
      q = p;
      for (int i = 0; i < k + 1; i++) {
        if (q != NULL) {
          q = q->next;
        } else {
          return dump->next;      
        }
      }
      // deal with medial relations 
      former = p->next;
      latter = former->next;
      for (int i = 0; i < k - 1; i++) {
        // save latter->next as next latter
        nextLatter = latter->next;
        // latter->next = former
        latter->next = former;
        // save latter as next former  
        former = latter;
        latter = nextLatter;
      }
      // deal with head
      q = p->next;
      p->next = former;
      // deal with tail
      q->next = latter;

      p = q;
    }
    return dump->next;      
  }
  // 26. Remove Duplicates from Sorted Array
  int removeDuplicates(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int j = 1;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] != nums[i - 1]) {
        nums[j++] = nums[i];
      }
    } 
    return j;      
  }
  // 27. Remove Element
  int removeElement(vector<int>& nums, int val) {
    int j = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] != val) {
        nums[j++] = nums[i];
      }
    }
    return j;
  }
  // 28. Implement strStr()
  int strStr(string haystack, string needle) {
    if (needle.size() == 0) return 0;
    int hLen = haystack.size(), nLen = needle.size();
    for (int i = 0; i < hLen; i++) {
      if (hLen - i < nLen) {
        return -1;
      } else {
        if (haystack.substr(i, nLen).compare(needle) == 0) {
          return i;
        }
      }
    }
    return -1;
  }
  // 29. Divide Two Integers
  int divide_subtract(int dividend, int divisor) {
    if (dividend > INT32_MAX || dividend < INT32_MIN || divisor > INT32_MAX || divisor < INT32_MIN) return INT32_MAX;
    if (dividend == INT32_MIN && divisor == -1) return INT32_MAX;
    bool isNeg;
    if ((dividend >= 0 && divisor > 0) || (dividend < 0 && divisor < 0)) {
      isNeg = false;
    } else {
      isNeg = true;
    }
    long father = abs((long)dividend);
    long son = abs((long)divisor);
    long result = 0;
    if (son == 1) {
      if (isNeg) {
        return -father;
      } else {
        return father;
      }
    }
    while (father >= 0) {
      father -= son;
      result++;
    }
    result--;
    if (isNeg) {
      return -result;
    } else {
      return result;
    }
  }
  // 29. Divide Two Integers
  int divide(int dividend, int divisor) {
    if (dividend > INT32_MAX || dividend < INT32_MIN || divisor > INT32_MAX || divisor < INT32_MIN) return INT32_MAX;
    long son = abs((long)divisor), father = abs((long)dividend), res = 0, base = 1, sum = 0;
    for (int i = 31; i >= 0; i--) {
      if (sum + (son << i) <= father) {
        sum += son << i;
        res += base << i;
      }
    }
    if ((dividend >= 0 && divisor > 0) || (dividend < 0 && divisor < 0)) {
      return (res > INT32_MAX) ? INT32_MAX : res;
    } else {
      return (-res < INT32_MIN) ? INT32_MAX : -res;
    }
  }
  // 30. Substring with Concatenation of All Words
  vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> result;
    if (words.size() == 0 || words[0].size() == 0 || s.size() < words.size() * words[0].size()) {
      return result;
    }
    unordered_map<string, int> counts;
    for (string word : words) {
      if (counts.find(word) == counts.end()) {
        counts[word] = 1;
      } else {
        counts[word]++;
      }
    }
    int wordCount = words.size(), wordLength = words[0].size(), strLength = s.size();
    for (int i = 0; i <= strLength - wordLength * wordCount; i++) {
      unordered_map<string, int> innerCounts = counts;
      bool flag = true;
      for (int j = 0; j < wordCount; j++) {
        string nowStr = s.substr(i + j * wordLength, wordLength);
        if (innerCounts.find(nowStr) == innerCounts.end() || innerCounts[nowStr] == 0) {
          flag = false;
          break;
        } else {
          innerCounts[nowStr]--;
        }
      }
      if (flag) {
        result.push_back(i);
      }
    }
    return result;
  }

};

int main() {
  Solution s;
  cout << s.divide(-2147483648, 1) << endl;
  return 0;
}