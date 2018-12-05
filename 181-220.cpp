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
    // 187. Repeated DNA Sequences
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;
        if (s.size() <= 10)
            return res;

        unordered_map<string, int> cntMap;
        for (int i = 0; i + 9 < s.size(); i++) {
            string now = s.substr(i, 10);
            if (cntMap.find(now) == cntMap.end()) {
                cntMap[now] = 1;
            } else {
                if (cntMap[now] == 1) {
                    cntMap[now] = 2;
                    res.push_back(now);
                }
            }
        }
        return res;
    }

    // 189. Rotate Array
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        k = k % len;
        int count = 0;
        for (int i = 0; count < len; i++) {
            int next = (i + k) % len;
            int prevInt = nums[i];
            while (true) {
                int temp = nums[next];
                nums[next] = prevInt;
                next = (next + k) % len;
                count++;
                prevInt = temp;
                if (next == (i + k) % len)
                    break;
            }
        }    
    }

    // 190. Reverse Bits
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for (int i = 0; i < 32; i++)
            res |= (n >> i & 1) << (31 - i);
        return res;
    }

    // 191. Number of 1 Bits
    int hammingWeight(uint32_t n) {
        int sum = 0;
        while (n > 0) {
            sum++;
            n &= n - 1;
        }
        return sum;
    }

    // 198. House Robber
    int rob(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int first, second;
        first = nums[0];
        if (nums.size() == 1)
            return first;
        second = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            int oldSecond = second;
            second = max(nums[i] + first, second);
            first = oldSecond;
        }        
        return max(first, second);
    }

    // 199. Binary Tree Right Side View
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (root == NULL)
            return res;
        queue<pair<TreeNode*, int> > bfsQueue;
        bfsQueue.push({root, 1});
        while (!bfsQueue.empty()) {
            TreeNode *nowNode = bfsQueue.front().first;
            int nowDepth = bfsQueue.front().second;
            bfsQueue.pop();
            if (nowDepth > res.size())
                res.push_back(nowNode->val);
            else
                res[nowDepth - 1] = nowNode->val;
            if (nowNode->left != NULL)
                bfsQueue.push({nowNode->left, nowDepth + 1});
            if (nowNode->right != NULL)
                bfsQueue.push({nowNode->right, nowDepth + 1});
        }
        return res;
    }

    // 201. Bitwise AND of Numbers Range
    int rangeBitwiseAnd(int m, int n) {
        if (m == n)
            return m;
        int i = 0;
        while (m != n) {
            m >>= 1;
            n >>= 1;
            i++;
        }
        return m << i;
    }

    // 202. Happy Number
    bool isHappy(int n) {
        set<int> uniqSet;
        while (n != 1 && uniqSet.find(n) == uniqSet.end()) {
            uniqSet.insert(n);
            int sum = 0;
            while (n > 0) {
                sum += pow(n % 10, 2);
                n /= 10;
            }
            n = sum;
        }
        return n == 1;
    }

    // 203. Remove Linked List Elements
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dump = new ListNode(0), *p = dump;
        dump->next = head;
        while (p->next != NULL) {
            if (p->next->val == val) {
                p->next = p->next->next;
            } else {
                p = p->next;
            }
        }
        return dump->next;    
    }

    // 204. Count Primes
    int countPrimes(int n) {
        if (n <= 2)
            return 0;
        vector<int> primes;
        for (int i = 3; i < n; i = i + 2) {
            bool isPrime = true;
            for (int j = 0; j < primes.size() && primes[j] * primes[j] <= i; j++) {
                if (i % primes[j] == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime)
                primes.push_back(i);
        }
        return primes.size() + 1;
    }

    // 205. Isomorphic Strings
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size())
            return false;
        unordered_map<char, char> charMap;
        unordered_map<char, char> charMap2;
        for (int i = 0; i < s.size(); i++) {
            if (charMap.find(t[i]) == charMap.end() && charMap2.find(s[i]) == charMap2.end()) {
                charMap[t[i]] = s[i];
                charMap2[s[i]] = t[i];
            } else {
                if (charMap[t[i]] != s[i] || charMap2[s[i]] != t[i])
                    return false;
            }
        }
        return true;
    }

    // 207. Course Schedule
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if (numCourses <= 0)
            return true;
        // pair<inNodesCnt, outNodes>
        vector<pair<int, vector<int> > > graph;
        for (int i = 0; i < numCourses; i++) {
            graph.push_back({0, {}});
        }
        for (int i = 0; i < prerequisites.size(); i++) {
            int start = prerequisites[i].first;
            int end = prerequisites[i].second;
            graph[start].second.push_back(end);
            graph[end].first++;
        }
        int oldCnt = -1, newCnt = 0;
        while (newCnt != oldCnt) {
            oldCnt = newCnt;
            for (int i = 0; i < graph.size(); i++) {
                if (graph[i].first == 0) {
                    graph[i].first = -1;
                    newCnt++;
                    for (int j = 0; j < graph[i].second.size(); j++)
                        graph[graph[i].second[j]].first--;
                }
            }
        }

        return (newCnt == numCourses);
    }

    // 209. Minimum Size Subarray Sum
    int minSubArrayLen(int s, vector<int>& nums) {
        // expand and shrink
        if (nums.size() == 0)
            return 0;
        int begin = 0, end = 0, sum = nums[begin], res = 0;
        while (end < nums.size() - 1) {
            // expand
            while (sum < s && end < nums.size()) {
                end++;
                sum += nums[end];
            }
            if (sum < s)
                return res;
            // shrink
            while (sum >= s && begin <= end) {
                sum -= nums[begin];
                begin++;
            }
            if (res == 0 || end - begin + 2 < res)
                res = end - begin + 2;
        }
        return res;
    }

    // 210. Course Schedule II
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> res;
        if (numCourses <= 0)
            return res;
        // pair<inNodesCnt, outNodes>
        vector<pair<int, vector<int> > > graph;
        for (int i = 0; i < numCourses; i++) {
            graph.push_back({0, {}});
        }
        for (int i = 0; i < prerequisites.size(); i++) {
            int start = prerequisites[i].first;
            int end = prerequisites[i].second;
            graph[start].second.push_back(end);
            graph[end].first++;
        }
        queue<int> bfsQueue;
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].first == 0)
                bfsQueue.push(i);
        }
        while (!bfsQueue.empty()) {
            int now = bfsQueue.front();
            res.push_back(now);
            bfsQueue.pop();
            for (int i = 0; i < graph[now].second.size(); i++) {
                int outNode = graph[now].second[i];
                graph[outNode].first--;
                if (graph[outNode].first == 0)
                    bfsQueue.push(outNode);
            }
        }
        reverse(res.begin(), res.end());
        return (res.size() == numCourses) ? res : vector<int>();
    }

    void printArr(vector<int>& nums) {
        for (int num: nums)
            cout << num << ", ";
        cout << endl;
    }
};

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isWord;
    TrieNode(): isWord(false) {}
};

// 208. Implement Trie (Prefix Tree)
class Trie {
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        delete root;
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            if (cur->children.find(ch) == cur->children.end()) {
                cur->children[ch] = new TrieNode();
            }
            cur = cur->children[ch];
        }
        cur->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            if (cur->children.find(ch) == cur->children.end()) {
                return false;
            } else {
                cur = cur->children[ch];
            }
        }
        return cur->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            char ch = prefix[i];
            if (cur->children.find(ch) == cur->children.end()) {
                return false;
            } else {
                cur = cur->children[ch];
            }
        }
        return true;
    }
};

int main() {
    int m = 2147483646;
    int n = 2147483647;
    Solution solution;
    Trie trie;

    trie.insert("apple");
    cout << boolalpha << trie.search("apple");   // returns true
    cout << boolalpha << trie.search("app");     // returns false
    // cout << boolalpha << trie.startsWith("app"); // returns true
    trie.insert("app");   // returns true
    cout << boolalpha << trie.search("app");     // returns false
}