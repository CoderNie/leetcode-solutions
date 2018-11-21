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
    // 81. Search in Rotated Sorted Array II
    bool search(vector<int>& nums, int target) {
        return true;
    }

    // 82. Remove Duplicates from Sorted List II
    ListNode* deleteDuplicates82(ListNode* head) {
        ListNode *frontHead = new ListNode(0), *p, *frontDup;
        frontHead->next = head;
        p = frontHead;
        bool isDup = false;
        while (p->next != NULL && p->next->next != NULL) {
        if (p->next->val == p->next->next->val) {
            if (!isDup) {
            isDup = true;
            frontDup = p;
            if (p->next->next->next == NULL) {
                frontDup->next = NULL;
                return frontHead->next;
            }
            }
            p = p->next;
        } else {
            if (isDup) {
            isDup = false;
            frontDup->next = p->next->next;
            p = frontDup;
            } else {
            p = p->next;
            }
        }
        } 
        return frontHead->next;
    }

    // 83. Remove Duplicates from Sorted List
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *p = head, *nextNode;

        while (p != NULL) {
            nextNode = p->next;
            while (nextNode != NULL && nextNode->val == p->val)
                nextNode = nextNode->next;
            p->next = nextNode;
            p = p->next;
        }

        return head;    
    }

    // 84. Largest Rectangle in Histogram
    int largestRectangleArea_brute(vector<int>& heights) {
        int largestArea = 0;
        for (int i = 0; i < heights.size(); i++) {
        int count = 1;
        for (int left = i - 1; left >= 0; left--)
            if (heights[left] >= heights[i]) count++;
            else break;
        for (int right = i + 1; right < heights.size(); right++)
            if (heights[right] >= heights[i]) count++;
            else break;
        largestArea = max(largestArea, count * heights[i]);
        }
        return largestArea;
    }

    int largestRectangleArea(vector<int> &heights) {
        int largestArea = 0, length = heights.size(), p;
        if (length == 0) return 0;
        int lessLeft[length], lessRight[length];
        lessLeft[0] = -1;
        lessRight[length - 1] = length;
        for (int i = 1; i < length; i++) {
        p = i - 1;
        while (p >= 0 && heights[p] >= heights[i])
            p = lessLeft[p];
        lessLeft[i] = p;
        }
        for (int i = length - 2; i >= 0; i--) {
        p = i + 1;
        while (p <= length && heights[p] >= heights[i])
            p = lessRight[p];
        lessRight[i] = p;
        }
        for (int i = 0; i < length; i++)
        largestArea = max(largestArea, (lessRight[i] - lessLeft[i] - 1) * heights[i]);
        return largestArea;
    }

    // 85. Maximal Rectangle
    int maximalRectangle(vector<vector<char> > &matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int m = matrix.size(), n = matrix[0].size();
        int maxArea = 0;
        bool dp[m + 1][n + 1];
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int p = 0; p <= m - i; p++) dp[p][0] = true;
            for (int q = 0; q <= n - j; q++) dp[0][q] = true;
            for (int p = 1; p <= m - i; p++) {
            for (int q = 1; q <= n - j; q++) {
                if (dp[p - 1][q] && dp[p][q - 1] && matrix[i + p - 1][j + q - 1] == '1') {
                dp[p][q] = true;
                maxArea = max(maxArea, p * q);
                } else {
                dp[p][q] = false;
                }
            }
            }
        }
        }
        return maxArea;
    }

    // 86. Partion List
    ListNode* partition(ListNode* head, int x) {
        ListNode* p = head;
        vector<int> before, after;
        while (p != NULL) {
        if (p->val < x) before.push_back(p->val);
        else after.push_back(p->val);
        p = p->next;
        }
        p = head;
        for (int i = 0; i < before.size(); i++) {
        p->val = before[i];
        p = p->next;
        }
        for (int i = 0; i < after.size(); i++) {
        p->val = after[i];
        p = p->next;
        }
        return head;
    }

    // 88. Merge Sorted Array
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p = m - 1, q = n - 1;
        for (int i = m + n - 1; i >= 0; i--) {
        if (p < 0) nums1[i] = nums2[q--];
        else if (q < 0) nums1[i] = nums1[p--];
        else nums1[i] = nums1[p] > nums2[q] ? nums1[p--] : nums2[q--];
        }
    }

    // 89. Gray Code
    vector<int> grayCode(int n) {
        vector<int> result, leftValue;
        for (int i = 0; i < pow(2, n); i++)
        leftValue.push_back(i);
        backTrackingGrayCode(result, leftValue, n);
        return result;
    }

    int indexOfArr(int x, vector<int> &leftValue) {
        for (int i = 0; i < leftValue.size(); i++) {
        if (x == leftValue[i]) return i;
        }
        return -1;
    }

    bool backTrackingGrayCode(vector<int> &result, vector<int> &leftValue, int n) {
        if (leftValue.empty()) {
        return true;
        } else {
        if (!result.empty()) {
            int last = result[result.size() - 1], temp, next, nextIndex;
            for (int pos = 0; pos < n; pos++) {
            temp = last / (pow(2, pos));
            temp = temp % 2;
            if (temp == 0) next = last + pow(2, pos);
            else next = last - pow(2, pos);
            nextIndex = indexOfArr(next, leftValue);
            if (nextIndex != -1) {
                leftValue.erase(leftValue.begin() + nextIndex);
                result.push_back(next);
                if (backTrackingGrayCode(result, leftValue, n)) {
                return true;
                } else {
                leftValue.insert(leftValue.begin() + nextIndex, next);
                result.erase(result.begin() + result.size() - 1);
                }
            } else {
                continue;
            }
            }
        } else {
            int size = leftValue.size();
            for (int pos = 0; pos < size; pos++) {
            int nowValue = leftValue[pos];
            leftValue.erase(leftValue.begin() + pos);
            result.push_back(nowValue);
            if (backTrackingGrayCode(result, leftValue, n)) {
                return true;
            } else {
                leftValue.insert(leftValue.begin() + pos, nowValue);
                result.erase(result.begin() + result.size() - 1);
            }
            }
        }
        }
        return false;
    }

    // 90. Subsets II
    vector<vector<int> > subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > subs;
        vector<int> sub;        
        backTrackingSubsetWithDup(subs, sub, nums, 0);
        return subs;
    }

    bool isSubsetExist(vector<int> &sub, vector<vector<int> > &subs) {
        for (int i = 0; i < subs.size(); i++) {
        if (subs[i].size() == sub.size()) {
            bool flag = true;
            for (int j = 0; j < sub.size(); j++)
            if (subs[i][j] != sub[j]) {
                flag = false;
                break;
            }
            if (flag) return true;
        }
        }
        return false;
    }

    void backTrackingSubsetWithDup(vector<vector<int> > &subs, vector<int> &sub, vector<int> &nums, int start) {
        vector<int> newSub = sub;
        sort(newSub.begin(), newSub.end());
        if (!isSubsetExist(newSub, subs)) {
        subs.push_back(newSub);
        }
        for (int i = start; i < nums.size(); i++) {
        sub.push_back(nums[i]);
        backTrackingSubsetWithDup(subs, sub, nums, i + 1);
        sub.erase(sub.end() - 1);
        }
    }

    void printMatrix(vector<vector<int> > matrix) {
        for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
        }
    }
    };

int main () {
    Solution s;
    vector<int> arr;
    arr = s.grayCode(10);
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}