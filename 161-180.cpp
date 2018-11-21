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
    // 162. Find Peak Element
    int findPeakElement(vector<int>& nums) {
        int begin = 0, end = nums.size() - 1, mid;
        while (begin < end) {
            mid = (begin + end) / 2;
            if (nums[mid] > nums[mid + 1]) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        }
        return begin;
    }

    // 167. Two Sum II - Input array is sorted
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        vector<int> res;
        while (i < j) {
            if (numbers[i] + numbers[j] > target) {
                j--;
            } else if (numbers[i] + numbers[j] < target) {
                i++;
            } else {
                res.push_back(i + 1);
                res.push_back(j + 1);
                break;
            }
        }
        return res;
    }
    // 168. Excel Sheet Column Title
    string convertToTitle(int n) {
        string res = "";
        int now;
        while (n > 0) {
            now = n % 26;
            n = n / 26;
            if (now == 0)
                n--;
            res.push_back('A' + (now + 25) % 26);
        }
        reverse(res.begin(), res.end());
        return res;
    }

    // 169. Majority Element
    int majorityElement(vector<int>& nums) {
        int now = nums[0], times = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == now) {
                times++;
            } else if (times > 0) {
                times--;
            } else {
                now = nums[i];
                times = 1;
            }
        }
        return now;
    }

    // 171. Excel Sheet Column Number
    int titleToNumber(string s) {
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            res *= 26;
            res += s[i] - 'A' + 1;
        }    
        return res;
    }

    // 172. Factorial Trailing Zeroes
    int trailingZeroes(int n) {
        int res = 0;
        while (n >= 5) {
            n /= 5;
            res += n;
        }
        return res;
    }

    // 179. Largest Number
    static bool divCompare(string a, string b) {
        return a + b > b + a;
    }

    string largestNumber(vector<int>& nums) {
        vector<string> strs;
        for (int num : nums)
            strs.push_back(to_string(num));
        
        sort(strs.begin(), strs.end(), divCompare);
        
        string res = "";
        for (string str : strs)
            res.append(str);
        
        while (res.size() > 1 && res[0] == '0')
            res.erase(res.begin());
        return res;
    }
};

int main() {
    int n;
    Solution s;
    vector<int> nums = {0, 0};
    cout << s.largestNumber(nums) << endl;
}