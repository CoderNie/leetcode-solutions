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

    void printArr(vector<int>& nums) {
        for (int num: nums)
            cout << num << ", ";
        cout << endl;
    }
};

int main() {
    int m = 2147483646;
    int n = 2147483647;
    Solution solution;
    vector<int> arr = {1, 2, 3, 4, 5, 6};
    solution.printArr(arr);
    solution.rotate(arr, 3);
    solution.printArr(arr);
    // string s, t;
    // while (cin >> s) {
    //     vector<string> res = solution.findRepeatedDnaSequences(s);
    //     for (string str: res) {
    //         cout << str << ", ";
    //     }
    //     cout << endl;
    // }
}