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

/* Definition for undirected graph. */
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

/* Definition for singly-linked list with a random pointer. */
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};


class Solution {
public:
    // 131. Palindrome Partitioning
    bool isPalindrome(string s) {
        if (s.size() <= 1) {
            return true;
        } else {
            int length = s.size();
            for (int i = 0; i < length / 2; i++) {
                if (s[i] != s[length - i - 1])
                    return false;
            }
            return true;
        }
    }
    vector<vector<string> > partition(string s) {
        vector<vector<string> > res;
        if (s.size() == 0) {
            res.push_back({});
        } else if (s.size() == 1) {
            res.push_back({s});
        } else {
            int length = s.size();
            for (int i = 1; i < length; i++) {
                string head = s.substr(0, i);
                if (isPalindrome(head)) {
                    string tail = s.substr(i, length - i);
                    vector<vector<string> > sonRes = partition(tail);
                    for (int j = 0; j < sonRes.size(); j++) {
                        sonRes[j].insert(sonRes[j].begin(), head);
                        res.push_back(sonRes[j]);
                    }
                }
            }
            if (isPalindrome(s)) {
                res.push_back({s});
            }
        }
        return res;
    }

    void printMatrix(vector<vector<string> > &mat) {
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[i].size(); j++) {
                cout << mat[i][j] << ", ";
            }
            cout << endl;
        }
    }

    // 133. Clone Graph
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL)
            return NULL;
        unordered_map<int, UndirectedGraphNode*> oldMapNew;
        UndirectedGraphNode *root = node;
        // copy nodes
        queue<UndirectedGraphNode* > bfsQueue;
        UndirectedGraphNode *newRoot = cloneNode(root);
        oldMapNew[root->label] = newRoot;
        bfsQueue.push(root);
        while (!bfsQueue.empty()) {
            UndirectedGraphNode* nowNode = bfsQueue.front();
            bfsQueue.pop();
            //oldMapNew[nowNode->label]->neighbors = {};
            for (int i = 0; i < nowNode->neighbors.size(); i++) {    
                if (oldMapNew.find(nowNode->neighbors[i]->label) == oldMapNew.end()) {
                    UndirectedGraphNode *newNode = cloneNode(nowNode->neighbors[i]);
                    oldMapNew[nowNode->neighbors[i]->label] = newNode;
                    bfsQueue.push(nowNode->neighbors[i]);
                }
                oldMapNew[nowNode->label]->neighbors.push_back(oldMapNew[nowNode->neighbors[i]->label]);
            }
        }
        return oldMapNew[root->label];

    }
    UndirectedGraphNode* cloneNode(UndirectedGraphNode *node) {
        if (node == NULL)
            return NULL;
        UndirectedGraphNode *newNode = new UndirectedGraphNode(node->label);
        return newNode;
    }
    void printGraph(UndirectedGraphNode* root) {
        if (root == NULL)
            return;
        cout << root->label << " neighbors.size = "  <<  root->neighbors.size() << endl;
        for (int i = 0; i < root->neighbors.size(); i++) {
            //cout << root->neighbors[i]->label << endl;
            printGraph(root->neighbors[i]);
        }
    }

    // 134. Gas Station
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        if (gas.size() == 0)
            return -1;
        int begin = 0,  beforeSum = 0;
        int i, sum, balance;
        while (begin < gas.size()) {
            balance = gas[begin] - cost[begin];
            if (balance >= 0) {
                sum = balance;
                i = begin + 1;
                while (sum >= 0 && i < gas.size()) {
                    balance = gas[i] - cost[i];
                    sum += balance;
                    i++;
                }
                if (sum >= 0) {
                    if (sum + beforeSum >= 0) {
                        return begin;
                    } else {
                        return -1;
                    }
                } else {
                    beforeSum += sum;
                    begin = i;
                    // cout << "beforeSum: " << beforeSum << " -- NextBegin: " << begin << endl;
                }
            } else {
                beforeSum += balance;
                begin++;
                // cout << "beforeSum: " << beforeSum << " -- NextBegin: " << begin << endl;
            }
        }
        return -1;
    }

    // 136. Single Number 
    int singleNumber1(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++)
            res ^= nums[i];
        return res;   
    }

    // 137. Single Number II
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            int sum = 0;
            for (int j = 0; j < nums.size(); j++) {
                if ((nums[j] >> i & 1) == 1)
                    sum++;
            sum %= 3;
            if (sum != 0)
                res |= sum << i;
        }
        return res;
    }

    // 138. Copy List With Random Pointer
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == NULL)
            return NULL;
        unordered_map<RandomListNode*, RandomListNode*> oldMapNew;
        RandomListNode *newNode, *p = head;
        oldMapNew[head] = new RandomListNode(head->label);
        while (p != NULL) {
            newNode = oldMapNew[p];
            if (p->random != NULL) {
                if (oldMapNew.find(p->random) == oldMapNew.end())
                    oldMapNew[p->random] = new RandomListNode(p->random->label);
                newNode->random = oldMapNew[p->random];
            }
            if (p->next != NULL) {
                if (oldMapNew.find(p->next) == oldMapNew.end())
                    oldMapNew[p->next] = new RandomListNode(p->next->label);
                newNode->next = oldMapNew[p->next];
            }
            p = p->next;
        }
        return oldMapNew[head];
    }

    // 139. Word Break
    bool isBelongTo(string s, vector<string>& wordDict) {
        for (int i = 0; i < wordDict.size(); i++) {
            if (s == wordDict[i])
                return true;
        }
        return false;
    }
    bool wordBreak1(string s, vector<string>& wordDict) {
        int length = s.size();
        if (length == 0) 
            return true;
        bool dp[length];
        for (int i = 0; i < length; i++) {
            dp[i] = false;
            if (isBelongTo(s.substr(0, i + 1), wordDict)) {
                dp[i] = true;
                continue;
            }
            for (int j = 0; j < i; j++) {
                if (dp[j] && isBelongTo(s.substr(j + 1, i - j), wordDict)) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[length - 1];
    }

    // 140. Word Break II
    unordered_map<string, vector<string> > resMap;


    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if (resMap.find(s) != resMap.end())
            return resMap[s];
        vector<string> res;
        int length = s.size();
        if (length == 0)
            return res;
        for (int i = 0; i < length - 1; i++) {
            string head = s.substr(0, i + 1);
            string tail = s.substr(i + 1, length - i - 1);
            // cout << head << "--" << tail << endl;
            if (isBelongTo(head, wordDict)) {
                if (resMap.find(tail) == resMap.end()) {
                    resMap[tail] = wordBreak(tail, wordDict);
                }
                vector<string> subRes = resMap[tail];
                for (int j = 0; j < subRes.size(); j++) {
                    res.push_back(head + " " + subRes[j]);
                }
            }
        }
        if (isBelongTo(s, wordDict)) {
            res.push_back(s);
        }
        resMap[s] = res;
        return res;
    }
};

int main () {
    Solution s;
    vector<string> wordDict = {"aaaa", "aa", "a"};
    vector<string> res = s.wordBreak("aaaaaaa", wordDict);
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << endl;
}