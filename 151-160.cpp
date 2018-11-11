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

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // 151. Reverse Words in String
    void trimWords(string &s) {
        if (s.size() == 0)
            return;
        int length = s.size();
        int i = 0;
        while (i < length && s[i] == ' ')
            i++;
        if (i > 0)
            s.erase(s.begin(), s.begin() + i);
        length = s.size();
        int j = length - 1;
        while (j >= 0 && s[j] == ' ')
            j--;
        if (j < length - 1)
            s.erase(s.end() - (length - j) + 1, s.end());
    }
    void reverseWords(string &s) {
        trimWords(s);
        if (s.size() == 0)
            return;
        reverse(s.begin(), s.end());
        int begin = 0, end = 0;
        while (end < s.size()) {
            while (s[end] != ' ' && end < s.size())
                end++;
            reverse(s.begin() + begin, s.begin() + end);
            begin = ++end;
            while (begin < s.size() && s[begin] == ' ')
                s.erase(s.begin() + begin);
        }
    }

    // 152. Maxium Product Subarray
    int maxProduct(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int imax = nums[0], imin = nums[0], res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < 0)
                swap(imax, imin);
            imax = max(imax * nums[i], nums[i]);
            imin = min(imin * nums[i], nums[i]);
            res = max(res, imax);
        }
        return res;
    }

    // 153. Find Minimum in Rotated Sorted Array
    int findMin(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int begin = 0, end = nums.size() - 1, mid;
        while (begin < end) {
            mid = (begin + end) / 2;
            if (nums[begin] < nums[end]) {
                return nums[begin];
            } else if (nums[begin] < nums[mid]) {
                begin = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        return nums[begin];
    }

    // 160. Intersection of Two Linked Lists
    int getListLength(ListNode *head) {
        int res = 0;
        while (head != NULL) {
            head = head->next;
            res++;
        }
        return res;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = getListLength(headA);
        int lenB = getListLength(headB);
        if (lenA > lenB) {
            swap(lenA, lenB);œ
            swap(headA, headB);
        }
        for (int i = 0; i < (lenB - lenA); i++)
            headB = headB->next;
        while (headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }
};


class MinStack {
private:
    stack<int> dataStack;
    stack<int> minStack;
public:
    /** initialize your data structure here. */
    // MinStack() {
    // }
    
    void push(int x) {
        dataStack.push(x);
        if (minStack.empty() || x <= minStack.top())
            minStack.push(x);
    }
    
    void pop() {
        if (dataStack.top() == minStack.top())
            minStack.pop();
        dataStack.pop();
    }
    
    int top() {
        return dataStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

int main () {

    int a = 3, b = 4;
    cout << a << "--" << b << endl;
    swap(a, b);
    cout << a << "--" << b << endl;
    return 0;
}