#include <queue>
#include <vector>
#include <map>
#include <set>

#include <iostream>
#include <algorithm>
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
  // 1.二维有序数组查找
  bool Find(int target, vector<vector<int> > array) {
    if (array.size() == 0) return false;
    int i = array.size() - 1;
    int j = 0;
    while (i >= 0 && j < array[0].size()) {
      if (array[i][j] == target) {
        return true;
      } else if (array[i][j] < target) {
        j++;
      } else {
        i--;
      }
    }
    return false;
  }
  // 2.替换空格 6ms
  void replaceSpace(char *str,int length) {
    char *begin = str;
    int newLength = length;
    for (int i = 0; i < length; i++) {
      if (*str == ' ') {
        newLength += 2;
      }
      str++;
    }
    char *oldEnd = begin + length - 1, *newEnd = begin + newLength - 1;
    *(newEnd + 1) = '\0';
    for (int i = 0; i < length; i++) {
      if (*oldEnd == ' ') {
        *newEnd = '0';
        *(newEnd - 1) = '2';
        *(newEnd - 2) = '%';
        newEnd -= 3;
      } else {
        *newEnd = *oldEnd;
        newEnd -= 1;
      }
      oldEnd--;
    }
	}
  // 3.从尾到头打印数组 4ms
  vector<int> printListFromTailToHead(ListNode* head) {
    vector<int> old;
    while (head != NULL) {
      old.push_back(head->val);
      head = head->next;
    }
    reverse(old.begin(), old.end());
    return old;
  }
  
};

int main() {
  Solution s;
  // vector<vector<int> > arr = {{4}, {3}};
  // cout << boolalpha << s.Find(9, arr) << endl;
  char str[] = " hello qwle world";
  cout << str << endl;
  s.replaceSpace(str, 17);
  cout << str << endl;
}