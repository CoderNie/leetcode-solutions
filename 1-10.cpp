#include <iostream>
#include <queue>
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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    queue<int> left, right;
    while (l1 != NULL) {
      left.push(l1->val);
      l1 = l1->next;
    }
    while (l2 != NULL) {
      right.push(l2->val);
      l2 = l2->next;
    }
    ListNode *now = NULL, *res;
    int jin = 0, sum;
    while (!left.empty() || !right.empty()) {
      sum = 0;
      if (!left.empty()) {
        sum += left.front();
        left.pop();
      }
      if (!right.empty()) {
        sum += right.front();
        right.pop();
      }
      sum += jin;
      jin = sum / 10;
      sum %= 10;
      ListNode newNode(sum);
      if (now == NULL) {
        cout << "null here..." << endl;
        now = &newNode;
      }
      res = &newNode;
      // cout << (*now)->val << endl;
      res->next = NULL;
      res = res->next;
    }
    return now;
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
    // map<char, int> myMap;
    // // myMap.find(s[j]);
    // for (int i = 0, j = 0; j < s.size(); j++){
    //   if (myMap.find(s[j]) == myMap.end()) {
    //     myMap.insert({s[j], j});
    //   } else {
    //   }
    // }
    return 0;
  }

};

int main () {
  Solution s;
  cout << s.lengthOfLongestSubstring("abcabcbb") << endl;
  // -------1--------
  // ListNode* a;
  // ListNode A1(2), A2(4), A3(3), B1(5), B2(6), B3(4);
  // A1.next = &A2;
  // A2.next = &A3;
  // B1.next = &B2;
  // B2.next = &B3;
  // a = s.addTwoNumbers(&A1, &B1);
  // while (a != NULL) {
  //   cout << a->val << "\t";
  //   a = a->next;
  // }
  // cout << "aaa" << endl;
  return 0;
}