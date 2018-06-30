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

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  // 61. Rotate List
  ListNode* rotateRight(ListNode* head, int k) {
    if (head == NULL || head->next == NULL) return head;
    ListNode *p = head;
    int length = 1;
    while (p->next != NULL) {
      length++;
      p = p->next;
    }
    p->next = head;
    k = k % length;
    p = head;
    for (int i = 1; i < length - k; i++)
      p = p->next;
    head = p->next;
    p->next = NULL;
    return head;
  }
};