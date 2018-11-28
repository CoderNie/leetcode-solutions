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
    // 91. Decode Ways
    int numDecodings(string s) {
        if (s.size() == 0 || s[0] == '0') {
        return 0;
        } else if (s.size() == 1) {
        return 1;
        } else {
        int count = 0;
        count += numDecodings(s.substr(1, s.size() - 1));
        if ((s[0] == '2' && s[1] <= '6') || s[0] == '1') {
            if (s.size() > 2) {
            count += numDecodings(s.substr(2, s.size() - 2));
            } else {
            count += 1;
            }
        }
        return count;
        }
    }

    int numDecodings_dp(string s) {
        if (s.size() <= 0) return 0;
        int n = s.size(), dp[n + 1];
        dp[n] = 1;
        dp[n - 1] = s[n - 1] == '0' ? 0 : 1;
        for (int i = n - 2; i >= 0; i--)
        if (s[i] == '0') dp[i] = 0;
        else dp[i] = dp[i + 1] + ((s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6') ? dp[i + 2] : 0));
        return dp[0];
    }


    // 92. Reverse Linked List II
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *p = head, *first, *after, *linshi, *before = new ListNode(0);
        before->next = head;
        p = before;
        for (int i = 0; i < m - 1; i++)
        p = p->next;
        first = p;
        p = p->next;

        after = p->next;
        for (int i = m; i < n; i++) {
        linshi = after->next;
        after->next = p;
        p = after;
        after = linshi;
        }
        first->next->next = after;
        first->next = p;
        return before->next;
    }

    bool isValid(string & s) {
        if (s.size() == 1) {
        return true;
        } else if (s.size() == 2) {
        if (s[0] != '0') return true;
        else return false;
        } else if (s.size() == 3) {
        if ((s[0] == '2' && (s[1] <= '4' || (s[1] == '5' && s[2] <= '5')) ) || s[0] == '1') return true;
        else return false;
        } else {
        return false;
        }
    }

    // 93. Restore IP Addresses
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        string s1, s2, s3, s4;
        int length = s.size();
        if (length < 4 || length > 12) return result;
        for (int i = 1; i <= 3; i++) {
        for (int j = i + 1; j <= i + 3 && j < length; j++) {
            for (int k = j + 1; k <= j + 3 && k < length; k++) {
            if (length - k <= 3) {
                s1 = s.substr(0, i);
                s2 = s.substr(i, j - i);
                s3 = s.substr(j, k - j);
                s4 = s.substr(k, length - k);
                if (isValid(s1) && isValid(s2) && isValid(s3) && isValid(s4)) {
                result.push_back(s1 + "." + s2 + "." + s3 + "." + s4);
                }
            }
            }
        }
        }
        return result;
    }

    // 95. Unique Binary Search Trees II
    vector<TreeNode*> generateTrees(int n) {
        return geneTrees(1, n);
    }

    vector<TreeNode*> geneTrees(int start, int end) {
        vector<TreeNode*> result;
        if (start == end) {
        result.push_back(new TreeNode(start));
        } else {
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> leftTrees, rightTrees;
            if (i - 1 >= start) {
            leftTrees = geneTrees(start, i - 1);
            } else {
            leftTrees.push_back(NULL);
            }
            if (i + 1 <= end) {
            rightTrees = geneTrees(i + 1, end);
            } else {
            rightTrees.push_back(NULL);
            }
            for (int p = 0; p < leftTrees.size(); p++) {
            for (int q = 0; q < rightTrees.size(); q++) {
                TreeNode* newTree = new TreeNode(i);
                newTree->left = leftTrees[p];
                newTree->right = rightTrees[q];
                result.push_back(newTree);
            }
            }
        }
        }
        return result;
    }


    // 96. Unique Binary Search Trees
    int numTrees(int n) {
        if (n <= 1) return 1;
        int dp[n + 1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
        dp[i] = 0;
        for (int pos = 0; pos < i; pos++) {
            dp[i] += dp[pos] * dp[i - pos - 1];
        }
        }
        return dp[n];
    }

    // 98. Validate Binary Search Tree
    bool isValidBST(TreeNode* root) {
        if (root == NULL) return true;
        vector<int> inList;
        inOrder(root, inList);
        for (int i = 0; i < inList.size() - 1; i++) {
        if (inList[i] >= inList[i + 1])
            return false;
        }
        return true;
    }

    void preOrder(TreeNode* p, vector<int> & preList) {
        if (p == NULL) {
        return;
        } else {
        preList.push_back(p->val);
        preOrder(p->left, preList);
        preOrder(p->right, preList);
        }
    }
    void inOrder(TreeNode* p, vector<int> & inList) {
        if (p == NULL) {
            return;
        } else {
            inOrder(p->left, inList);
            inList.push_back(p->val);
            inOrder(p->right, inList);
        }
    }
    void printList(vector<int> & list) {
        for (int i = 0; i < list.size(); i++)
        cout << list[i] << " ";
        cout << endl;
    }

    // 99. Recover Binary Search Tree
    void inOrderNodes(TreeNode* p, vector<TreeNode*> & inList) {
        if (p == NULL) {
            return;
        } else {
            inOrderNodes(p->left, inList);
            inList.push_back(p);
            inOrderNodes(p->right, inList);
        }
    }
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> nodeList;
        inOrderNodes(root, nodeList);
        int i = 0, j = nodeList.size() - 1;
        while (nodeList[i]->val < nodeList[i + 1]->val)
            i++;
        while (nodeList[j]->val > nodeList[j - 1]->val)
            j--;
        swap(nodeList[i]->val, nodeList[j]->val);
    }
        

    // 100. Same Tree
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == NULL && q == NULL) {
        return true;
        } else if (p != NULL && q != NULL) {
        return (p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
        } else {
        return false;
        }
    }
    };

    int main () {
    Solution s;
    vector<string> res = s.restoreIpAddresses("000256");
    for (string str : res) {
        cout << str << endl;
    }

    return 0;
    }