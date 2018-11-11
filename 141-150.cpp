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
    // 141. Linked List Cycle
    bool hasCycle(ListNode *head) {
        if (head == NULL)
            return false;
        ListNode *low = head, *fast = head;
        while (fast->next != NULL && fast->next->next != NULL) {
            low = low->next;
            fast = fast->next->next;
            if (low == fast)
                return true;
        }
        return false;
    }

    // 142. Linked List Cycle II
    int getCycleLength(ListNode *head) {
        if (head == NULL)
            return -1;
        ListNode *low = head, *fast = head;
        bool hasCycle = false;
        while (fast->next != NULL && fast->next->next != NULL) {
            low = low->next;
            fast = fast->next->next;
            if (low == fast) {
                hasCycle = true;
                break;
            }
        }
        if (hasCycle) {
            int length = 0;
            do {
                low = low->next;
                fast = fast->next->next;
                length++;
            } while (low != fast);
            return length;
        } else {
            return -1;
        }
    }
    ListNode *detectCycle(ListNode *head) {
        int cycleLength = getCycleLength(head);
        if (cycleLength == -1) {
            return NULL;
        } else {
            ListNode *first = head, *second = head;
            for (int i = 0; i < cycleLength; i++)
                first = first->next;
            while (first != second) {
                first = first->next;
                second = second->next; 
            }
            return first;
        }
    }

    // 143. Reorder List
    ListNode *reverseList(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *first = head, *second = head->next, *after;
        while (second != NULL) {
            after = second->next;
            second->next = first;
            first = second;
            second = after;
        }
        head->next = NULL;
        return first; 
    }
    ListNode *mergeTwoList(ListNode *p1, ListNode *p2) {
        ListNode *dump = new ListNode(0), *p = dump;
        while (p1 != NULL && p2 != NULL) {
            p->next = p1;
            p = p->next;
            p1 = p1->next;
            p->next = p2;
            p = p->next;
            p2 = p2->next;
        }
        if (p1 != NULL)
            p->next = p1;
        if (p2 != NULL)
            p->next = p2;
        return dump->next;
    }
    void reorderList(ListNode *head) {
        /*
            three step: 1.find the middle -> 2.reverse the second half -> 3.merge two linkedlist
        */
        if (head == NULL || head->next == NULL) 
            return;
        // 1.find the middle
        ListNode *low = head, *fast = head;
        while (fast->next != NULL && fast->next->next != NULL) {
            low = low->next;
            fast = fast->next->next;
        }
        ListNode *p1 = head, *p2 = low->next;
        // cut the linkedlist
        low->next = NULL;
        printList(p1);
        printList(p2);

        // 2. reverse the second half
        p2 = reverseList(p2);

        // 3. merge two linkedlist
        mergeTwoList(p1, p2);
    }

    // 144. Binary Tree Preorder Traversal
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == NULL)
            return res;
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        while (!nodeStack.empty()) {
            TreeNode *nowNode = nodeStack.top();
            nodeStack.pop();
            res.push_back(nowNode->val);
            if (nowNode->right != NULL)
                nodeStack.push(nowNode->right);
            if (nowNode->left != NULL)
                nodeStack.push(nowNode->left);
        }
        return res;
    }

    // 145. Binary Tree Postorder Traversal
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == NULL)
            return res;
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        while (!nodeStack.empty()) {
            TreeNode* nowNode = nodeStack.top();
            nodeStack.pop();
            res.push_back(nowNode->val);
            if (nowNode->left != NULL)
                nodeStack.push(nowNode->left);
            if (nowNode->right != NULL)
                nodeStack.push(nowNode->right);
        }
        reverse(res.begin(), res.end());
        return res;
    }

    // 147. Insertion Sort List
    ListNode* insertionSortList(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *dump = new ListNode(0);
        dump->next = head;
        
        ListNode *p = head->next, *after, *before = head;
        while (p != NULL) {
            after = p->next;

            ListNode *i = dump;
            while (i->next->val <= p->val && i->next != p)
                i = i->next;
            if (i->next != p) {
                before->next = after;
                p->next = i->next;
                i->next = p;
            } else {
                before = p;
            }
            p = after;
        }
        return dump->next;
    }

    // 148. Sort List
    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;

        // 1.find the middle
        ListNode *low = head, *fast = head;
        while (fast->next != NULL && fast->next->next != NULL) {
            low = low->next;
            fast = fast->next->next;
        }
        ListNode *p1 = head, *p2 = low->next;
        // cut the linkedlist
        low->next = NULL;
            
        p1 = sortList(p1);
        p2 = sortList(p2);

        return mergeSortList(p1, p2);
    }
    ListNode *mergeSortList(ListNode* p1, ListNode* p2) {
        ListNode *dump = new ListNode(0), *p = dump;
        while (p1 != NULL && p2 != NULL) {
            if (p1->val < p2->val) {
                p->next = p1;
                p1 = p1->next;
            } else {
                p->next = p2;
                p2 = p2->next;
            }
            p = p->next;
        }
        if (p1 != NULL)
            p->next = p1;
        if (p2 != NULL)
            p->next = p2;
        return dump->next;
    }

    ListNode *constructListNode(vector<int> &arr) {
        ListNode *dump = new ListNode(0), *p = dump; 
        for (int i = 0; i < arr.size(); i++) {
            p->next = new ListNode(arr[i]);
            p = p->next;
        }
        return dump->next;
    }

    void printList(ListNode *head) {
        while (head != NULL) {
            cout << head->val << "->";
            head = head->next;
        }
        cout << endl;
    }
};

class LRUCache {
public:
    // 146. LRU Cache
    LRUCache(int capacity) {
        
    }
    
    int get(int key) {
        return 0;
    }
    
    void put(int key, int value) {
        
    }
};

int main () {
    Solution s;
    vector<int> arr = {3, 4, 5, 1, 2, 6};
    ListNode* list = s.constructListNode(arr);
    s.printList(list);
    s.printList(s.insertionSortList(list));
}