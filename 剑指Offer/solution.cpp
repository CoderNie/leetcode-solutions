#include <queue>
#include <vector>
#include <map>
#include <set>
#include <stack>

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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
  stack<int> stack1;
  stack<int> stack2;
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
  // 4.重建二叉树 5ms
  TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
    if (pre.size() == 0) return 0;
    TreeNode *root = new TreeNode(pre[0]), *p;
    map<int, int> indexMap;
    for (int i = 0; i < vin.size(); i++)
      indexMap[vin[i]] = i;
    for (int i = 1; i < pre.size(); i++) {
      p = root;
      while (true) {
        if (indexMap[pre[i]] > indexMap[p->val]) {
          if (p->right == NULL) {
            p->right = new TreeNode(pre[i]);
            break;
          } else {
            p = p->right;
          }
        } else {
          if (p->left == NULL) {
            p->left = new TreeNode(pre[i]);
            break;
          } else {
            p = p->left;
          }
        }
      }
    }
    return root;
  }
  vector<int> inOrderTraverse(TreeNode* root) {
    vector<int> res, left, right;
    if (root != NULL) {
      left = inOrderTraverse(root->left);
      res.insert(res.end(), left.begin(), left.end());
      res.push_back(root->val);
      right = inOrderTraverse(root->right);
      res.insert(res.end(), right.begin(), right.end());
    }
    return res;
  }
  vector<int> preOrderTraverse(TreeNode* root) {
    vector<int> res, left, right;
    if (root != NULL) {
      res.push_back(root->val);
      left = preOrderTraverse(root->left);
      res.insert(res.end(), left.begin(), left.end());
      right = preOrderTraverse(root->right);
      res.insert(res.end(), right.begin(), right.end());
    }
    return res;
  }
  // 5.用两个栈实现队列 3ms
  void push(int node) {
    stack1.push(node);
  }
  int pop() {
    while (!stack1.empty()) {
      stack2.push(stack1.top());
      stack1.pop();
    }
    int res = stack2.top();
    stack2.pop();
    while (!stack2.empty()) {
      stack1.push(stack2.top());
      stack2.pop();
    }
    return res;
  }
  // 6.旋转数组的最小数字 32ms
  int minNumberInRotateArray(vector<int> rotateArray) {
    if (rotateArray.size() == 0) return 0;
    int minIndex = 0, maxIndex = rotateArray.size() - 1, nowIndex, nowMin = rotateArray[0];
    while (minIndex <= maxIndex) {
      nowIndex = (maxIndex + minIndex) / 2;
      if (rotateArray[nowIndex] > nowMin) {
        minIndex = nowIndex + 1;
      } else {
        nowMin = rotateArray[nowIndex];
        maxIndex = nowIndex - 1;
      }
    }
    return nowMin;
  }
  // 7.剑指Offer 5ms
  int Fibonacci(int n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;
    int first = 1, second = 1, now;
    for (int i = 0; i < n - 2; i++) {
      now = first + second;
      first = second;
      second = now;
    }
    return now;
  }
  // 8.跳台阶 3ms
  int jumpFloor(int number) {
    if (number == 0) return 0;
    return Fibonacci(number + 1);      
  }
  // 9.变态跳台阶 3ms
  int jumpFloorII(int number) {
    if (number == 0) return 0;
    return pow(2, number - 1);
  }
  // 10.矩形覆盖 4ms
  int rectCover(int number) {
    if (number == 0) return 0;
    return Fibonacci(number + 1); 
  }
  // 11.二进制中1的个数 3ms
  int  NumberOf1(int n) {
    int res = 0;
    bool flag = false;
    if (n < 0) {
      n = -1 * n - 1;
      flag = true;
    }
    while (n != 0) {
      if (n % 2 == 1) res++;
      n >>= 1;
    }
    return flag ? (32 - res) : res;
  }
  // 12.数值的整数次方 3ms
  double Power(double base, int exponent) {
    double res = 1;
    if (exponent >= 0) {
      for (int i = 0; i < exponent; i++) res *= base;
    } else {
      for (int i = 0; i < -exponent; i++) res /= base;
    }
    return res;
  }
  // 13.
  void reOrderArray(vector<int> &array) {
        
  }
  // 14.链表倒数第K个结点 4ms
  ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    ListNode *slow = pListHead, *fast = pListHead;
    for (int i = 0; i < k; i++) {
      if (fast == NULL) return NULL;
      fast = fast->next;
    }
    while (fast != NULL) {
      fast = fast->next;
      slow = slow->next;
    }
    return slow;
  }
  // 15.反转链表 4ms
  ListNode* ReverseList(ListNode* pHead) {
    if (pHead == NULL) return pHead;
    ListNode *after = NULL, *nextOne;
    while (pHead->next != NULL) {
      nextOne = pHead->next;
      pHead->next = after;
      after = pHead;
      pHead = nextOne;
    }
    pHead->next = after;
    return pHead;
  }

  // 66.机器人的运动范围 5ms
  bool isSuitable(int x, int y, int threshold) {
    int sum = 0;
    while (x > 0) {
      sum += x % 10;
      x /= 10;
    }
    while (y > 0) {
      sum += y % 10;
      y /= 10;
    }
    if (sum <= threshold) {
      return true;
    } else {
      return false;
    }
  }
  int movingCount(int threshold, int rows, int cols) {
    if (rows == 0 || cols == 0 || threshold < 0) return 0;
    queue<pair<int, int> > bfsQueue;
    bool isPassed[rows][cols];
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        isPassed[i][j] = false;
    bfsQueue.push({0, 0});
    isPassed[0][0] = true;
    int result = 0;
    int x, y;
    while (!bfsQueue.empty()) {
      pair<int, int> nowPoint = bfsQueue.front();
      x = nowPoint.first;
      y = nowPoint.second;
      bfsQueue.pop();
      result++;
      if (x + 1 < rows && !isPassed[x + 1][y] && isSuitable(x + 1, y, threshold)) {
        bfsQueue.push({x + 1, y});
        isPassed[x + 1][y] = true;
      }
      if (x - 1 >= 0 && !isPassed[x - 1][y] && isSuitable(x - 1, y, threshold)){
        bfsQueue.push({x - 1, y});
        isPassed[x - 1][y] = true;
      }
      if (y + 1 < cols && !isPassed[x][y + 1] && isSuitable(x, y + 1, threshold)) {
        bfsQueue.push({x, y + 1});
        isPassed[x][y + 1] = true;
      }
      if (y - 1 >= 0 && !isPassed[x][y - 1] && isSuitable(x, y - 1, threshold)) {
        bfsQueue.push({x, y - 1});
        isPassed[x][y - 1] = true;
      }
    }
    return result;
  }
  
};

int main() {
  Solution s;
  cout << s.movingCount(3, 100, 100) << endl;

}