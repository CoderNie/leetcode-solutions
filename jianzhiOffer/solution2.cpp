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


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    int InversePairs(vector<int> &data) {
        return inversePairsTraverse(data, 0, data.size() - 1);
    }
    long inversePairsTraverse(vector<int> &data, int begin, int end) {
        if (begin >= end) 
            return 0;
        int size1 = (end - begin) / 2 + 1;
        int i1 = begin, j1 = begin + size1 - 1, i2 = j1 + 1, j2 = end;
        long left = inversePairsTraverse(data, i1, j1);
        long right = inversePairsTraverse(data, i2, j2);
        // merge
        long count = 0;
        stack<int> temp;
        while (j1 >= i1 && j2 >= i2) {
            if (data[j1] >= data[j2]) {
                count += j2 - i2 + 1;
                count %= 1000000007;
                temp.push(data[j1--]);
            } else {
                temp.push(data[j2--]);
            }
        }
        while (j1 >= i1)
            temp.push(data[j1--]);
        while (j2 >= i2)
            temp.push(data[j2--]);

        while (!temp.empty()) {
            data[begin++] = temp.top();
            temp.pop();
        }
        return (left + right + count) % 1000000007;
    }
    void printArr(vector<int> &arr) {
        if (arr.size() <= 0) return;
        cout << arr[0];
        for (int i = 1; i < arr.size(); i++)
            cout << ", " << arr[i];
        cout << endl;
    }
//  37. 第一个公共结点
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if (pHead1 == NULL || pHead2 == NULL) return NULL;
        stack<ListNode*> l1, l2;
        while (pHead1 != NULL) {
            l1.push(pHead1);
            pHead1 = pHead1->next;
        }
        while (pHead2 != NULL) {
            l2.push(pHead2);
            pHead2 = pHead2->next;
        }
        ListNode *res = NULL;
        while (!l1.empty() && !l2.empty() && l1.top() == l2.top()) {
            res = l1.top();
            l1.pop();
            l2.pop();
        }
        return res;
    }
//  38. 数字在排序数组中出现的次数
    int GetNumberOfK(vector<int> data ,int k) {
        int begin = 0, end = data.size() - 1, mid;
        while (begin <= end) {
            mid = (end + begin) / 2;
            if (data[mid] >= k) {
                end = mid - 1;
            } else {
                begin = mid + 1;
            }
        }
        int before = end;
        begin = 0;
        end = data.size() - 1;
        while (begin <= end) {
            mid = (end + begin) / 2;
            cout << begin << mid << end << endl;
            if (data[mid] <= k) {
                begin = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        return (end - before);
    }
//  39. 二叉树的深度
    int TreeDepth(TreeNode* pRoot) {
        if (pRoot == NULL) {
            return 0;
        } else {
            int leftDepth = TreeDepth(pRoot->left);
            int rightDepth = TreeDepth(pRoot->right);
            return max(leftDepth, rightDepth) + 1;
        }

    }
//  39-1. 二叉树是否是平衡树
    bool IsBalanced_Solution(TreeNode* pRoot) {
        return (isBalanced(pRoot) != -1);
    }
    int isBalanced(TreeNode* pRoot) {
        if (pRoot == NULL) {
            return 0;
        } else {
            int leftDepth = isBalanced(pRoot->left);
            int rightDepth = isBalanced(pRoot->right);
            if (leftDepth >= 0 && rightDepth >= 0 && abs(leftDepth - rightDepth) <= 1) {
                return max(leftDepth, rightDepth) + 1;
            }
            return -1;
        }
    }
//  40. 数组中只出现一次的数字
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {

    }

//  41. 和为S的连续正数序列
    vector<vector<int> > FindContinuousSequence(int sum) {
        int z, x, y;
        vector<vector<int> > res;
        for (int c = 1; c <= sum; c++) {
            z = sum * 2 / (c + 1);
            if (z * (c + 1) == 2 * sum) {
                x = (z - c) / 2;
                if (x <= 0) {
                    break;
                } else if ((z - c) % 2 == 0) {
                    y = z - x;
                    vector<int> newArr;
                    for (int i = x; i <= y; i++) {
                        newArr.push_back(i);
                    }
                    res.push_back(newArr);
                }
            }
        }  
        reverse(res.begin(), res.end());
        return res;
    }
    void printMatrix(vector<vector<int> > & res) {
        for (int i = 0; i < res.size(); i++) {
            for (int j = 0; j < res[i].size(); j++) {
                cout << res[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Solution s;
    vector<vector<int> > res = s.FindContinuousSequence(15);
    cout << res.size() << endl;
    s.printMatrix(res);
}