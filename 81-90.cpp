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

/**
Definition for a binary tree node. */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  // 81. Search in Rotated Sorted Array II
  bool search(vector<int>& nums, int target) {
    return true;
  }

  // 82. Remove Duplicates from Sorted List II
  ListNode* deleteDuplicates(ListNode* head) {
    ListNode *frontHead = new ListNode(0), *p, *frontDup;
    frontHead->next = head;
    p = frontHead;
    bool isDup = false;
    while (p->next != NULL && p->next->next != NULL) {
      if (p->next->val == p->next->next->val) {
        if (!isDup) {
          isDup = true;
          frontDup = p;
          if (p->next->next->next == NULL) {
            frontDup->next = NULL;
            return frontHead->next;
          }
        }
        p = p->next;
      } else {
        if (isDup) {
          isDup = false;
          frontDup->next = p->next->next;
          p = frontDup;
        } else {
          p = p->next;
        }
      }
    } 
    return frontHead->next;
  }
};

int main () {
  return 0;
}