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

struct RandomListNode {
  int label;
  struct RandomListNode *next, *random;
  RandomListNode(int x) :
    label(x), next(NULL), random(NULL) {
  }
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
  // 13.调整数组顺序使奇数位于偶数前面
  void reOrderArray(vector<int> &array) {
    if (array.size() <= 1) return;
    int iX = 0, tail = array.size() - 1;
    vector<int> latter;
    for (int i = 0; i < array.size(); i++)
      if (array[i] % 2 == 1)
        array[iX++] = array[i];
      else
        latter.push_back(array[i]);
    for (int i = latter.size() - 1; i >= 0; i--)
      array[tail--] = latter[i];
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
  // 16.合并两个排序的链表
  ListNode* Merge(ListNode* pHead1, ListNode* pHead2){
    ListNode *dummy = new ListNode(0), *p = dummy;
    while (pHead1 != NULL && pHead2 != NULL) {
      if (pHead1->val <= pHead2->val) {
        p->next = pHead1;
        pHead1 = pHead1->next;
      } else {
        p->next = pHead2;
        pHead2 = pHead2->next;
      }
      p = p->next;
    }
    if (pHead1 != NULL) p->next = pHead1;
    else if (pHead2 != NULL) p->next = pHead2;
    return dummy->next; 
  }


  // 22.从上往下打印二叉树
  vector<int> PrintFromTopToBottom(TreeNode* root) {
    vector<int> res;
    if (root == NULL) return res; 
    queue<TreeNode* > myQueue;
    TreeNode* nowNode;
    myQueue.push(root);
    while (!myQueue.empty()) {
      nowNode = myQueue.front();
      myQueue.pop();
      res.push_back(nowNode->val);
      if (nowNode->left != NULL) myQueue.push(nowNode->left);
      if (nowNode->right != NULL) myQueue.push(nowNode->right);
    }
    return res;
  }

  // 24.二叉搜索树的后序遍历序列
  bool VerifySquenceOfBST(vector<int> sequence) {
    if (sequence.size() == 0)
      return false;
    vector<int> left;
    vector<int> right;
    int mid = sequence[sequence.size() - 1];
    int i = 0;
    while (sequence[i] < mid)
      left.push_back(sequence[i++]);
    while (sequence[i] > mid)
      right.push_back(sequence[i++]);
    if (i == sequence.size() - 1) {
      bool res = true;
      if (left.size() > 0)
        res = res && VerifySquenceOfBST(left);
      if (right.size() > 0)
        res = res && VerifySquenceOfBST(right);
      return res;
    } else {
      return false;
    }
  }
  // 25.二叉树中和为某一值的路径
  vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
    vector<vector<int> > res;
    if (root == NULL) return res;
    vector<int> path;
    dfs(root, expectNumber, path, res);
    return res;
  }
  void dfs(TreeNode* root, int expectNumber, vector<int> &path, vector<vector<int> > &res) {
    path.push_back(root->val);
    expectNumber -= root->val;
    if (root->left == NULL && root->right == NULL) {
      if (expectNumber == 0) {
        vector<int> newPath = path;
        res.push_back(newPath);
      }
    } else {
      if (root->left != NULL)
        dfs(root->left, expectNumber, path, res);
      if (root->right != NULL)
        dfs(root->right, expectNumber, path, res);
    }
    path.pop_back();
  }
  // 26.复杂链表的复制
  RandomListNode* Clone(RandomListNode* pHead) {
    // <old, new>
    map<RandomListNode*, RandomListNode*> myMap;
    RandomListNode *dummy = new RandomListNode(0), *p = dummy, *q = pHead;
    while (q != NULL) {
      RandomListNode *newNode = new RandomListNode(q->label);
      p->next = newNode;
      myMap[q] = newNode;
      p = p->next;
      q = q->next;
    }
    p = dummy->next;
    q = pHead;
    while (p != NULL) {
      if (q->random != NULL)
        p->random = myMap[q->random];
      p = p->next;
      q = q->next;
    }
    return dummy->next;
  }
  // 27.二叉搜索树与双向链表
  TreeNode* Convert(TreeNode* pRootOfTree) {
    if (pRootOfTree == NULL) return pRootOfTree;
    vector<TreeNode*> preList;
    preOrderTraverse27(pRootOfTree, preList);
    for (int i = 0; i < preList.size() - 1; i++) {
      preList[i]->right = preList[i + 1];
      preList[i + 1]->left = preList[i];
    }
    preList[0]->left = NULL;
    preList[preList.size() - 1]->right = NULL;
    return preList[0];
  }
  void preOrderTraverse27(TreeNode* root, vector<TreeNode*> &preList) {
    if (root != NULL) {
      preOrderTraverse27(root->left, preList);
      preList.push_back(root);
      preOrderTraverse27(root->right, preList);
    }
  }
  // 28.字符串的排列
  vector<string> Permutation(string str) {
    vector<string> resList;
    if (str.size() == 0) return resList;
    string res = "";
    sort(str.begin(), str.end());
    bool used[str.size()];
    for (int i = 0; i < str.size(); i++) used[i] = false;
    backTrack28(resList, res, str, used);
    return resList;
  }
  void backTrack28(vector<string> &resList, string &res, string &str, bool used[]) {
    if (res.size() == str.size()) {
      string newRes = res;
      resList.push_back(newRes);
    } else {
      for (int i = 0; i < str.size(); i++) {
        if ( used[i]  || (i > 0 && str[i] == str[i - 1] && !used[i - 1]) )
          continue;
        res = res + str[i];
        used[i] = true;
        backTrack28(resList, res, str, used);
        res.erase(res.size()-1, 1);
        used[i] = false;
      }
    }
  }

  // 29.数组中出现次数超过一半的数字
  int MoreThanHalfNum_Solution(vector<int> numbers) {
    if (numbers.size() == 1) return numbers[0];
    // number, count
    map<int, int> myMap;
    for (int number: numbers) {
      if (myMap.find(number) == myMap.end()) {
        myMap[number] = 1;
      } else {
        myMap[number]++;
        if (myMap[number] > (numbers.size() / 2))
          return number;
      }
    }
    return 0;
  }

  void partition(vector<int> &nums, int start, int end, int key) {
    int i = start, j = end, temp = nums[start];
    while (i < j) {
      while (i < j && nums[j] >= temp)
        j--;
      if (i < j)
        nums[i++] = nums[j];
      while (i < j && nums[i] <= temp)
        i++;
      if (i < j)
        nums[j--] = nums[i];
    }
    nums[i] = temp;
    if (i > key)
      partition(nums, start, i - 1, key);
    else if (i < key)
      partition(nums, i + 1, end, key);
  }
  // 30. 最小的 K 个数
  vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
    vector<int> res;
    if (k > input.size() || k == 0) return res;
    partition(input, 0, input.size() - 1, k - 1);
    for (int i = 0; i < k; i++)
      res.push_back(input[i]);
    return res;
  }

  // 31. 连续子数组的最大和
  int FindGreatestSumOfSubArray(vector<int> array) {
    
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
  vector<int> nums = {4,5,1,6,2,7,3,8};
  vector<int> res = s.GetLeastNumbers_Solution(nums, 1);
  for (int num: res) {
    cout << num << endl;
  }

}