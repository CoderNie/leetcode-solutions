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
    // 72. Simple Path
    string simplifyPath(string path) {
        stack<string> dirNames;
        string nowName = "", res = "";
        if (path.size() > 0 && path[path.size() - 1] != '/') path = path + "/";
        for (int i = 0; i < path.size(); i++) {
        if (path[i] == '/') {
            if (nowName.size() > 0) {
            if (nowName.compare("..") == 0) {
                if (!dirNames.empty()) dirNames.pop();
            } else if (nowName.compare(".") == 0) {

            } else {
                dirNames.push(nowName);
            }
            nowName = "";
            }
        } else {
            nowName += path[i];
        }
        }
        while (!dirNames.empty()) {
        res = "/" + dirNames.top() + res;
        dirNames.pop();
        }
        return res.size() > 0 ? res : "/";
    }

    // 73. Set Matrix Zeroes
    void setZeroes(vector<vector<int> > &matrix) {
        set<int> columnMarks, rowMarks;
        for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 0) {
            rowMarks.insert(i);
            columnMarks.insert(j);
            }
        }
        }
        for (int row: rowMarks)
        for (int j = 0; j < matrix[0].size(); j++)
            matrix[row][j] = 0;
        for (int column: columnMarks)
        for (int i = 0; i < matrix.size(); i++)
            matrix[i][column] = 0;
    }

    // 74. Search a 2D Matrix
    bool searchMatrix(vector<vector<int> >& matrix, int target) {
        if (matrix.size() < 1 || matrix[0].size() < 1) return false;
        int start = 0, end = matrix.size() - 1, mid;
        while (start <= end) {
        mid = (start + end) / 2;
        if (target < matrix[mid][0]) {
            end = mid - 1;
        } else if (target > matrix[mid][0]) {
            start = mid + 1;
        } else {
            return true;
        }
        }
        int row = matrix[mid][0] < target ? mid : mid - 1;
        if (row < 0) return false;
        start = 0;
        end = matrix[0].size() - 1;
        while (start <= end) {
        mid = (start + end) / 2;
        if (target < matrix[row][mid]) {
            end = mid - 1;
        } else if (target > matrix[row][mid]) {
            start = mid + 1;
        } else {
            return true;
        }
        } 
        return false;
    }

    // 75. Sort Colors
    void sortColors(vector<int>& nums) {
        int begin = 0, end = nums.size() - 1, cur = 0;
        while (cur <= end)
        if (nums[cur] == 0) swap(nums[cur++], nums[begin++]);
        else if (nums[cur] == 1) cur++;
        else swap(nums[cur], nums[end--]);
    }

    // 76. Minimum Window Substring
    string minWindow(string s, string t) {
        // char, count
        unordered_map<char, int> tMap, sMap;
        // count target letters
        for (char ch : t) {
            if (tMap.find(ch) == tMap.end()) {
                tMap[ch] = 1;
            } else {
                tMap[ch]++;
            }
        }
        int tSum = tMap.size(), sSum = 0, begin = 0;
        string res = "";
        // expand and shrink

        // expand
        for (int end = 0; end < s.size(); end++) {
            if (tMap.find(s[end]) == tMap.end()) {
                continue;
            } else {
                if (sMap.find(s[end]) == sMap.end()) {
                    sMap[s[end]] = 1;
                } else {
                    sMap[s[end]]++;
                }
                if (sMap[s[end]] == tMap[s[end]]) {
                    sSum++;
                }
                if (sSum == tSum) {
                    // shrink
                    while (begin < end) {
                        if (sMap.find(s[begin]) != sMap.end()) {
                            sMap[s[begin]]--;
                            if (sMap[s[begin]] < tMap[s[begin]]) {
                                sSum--;
                                break;
                            }
                        }
                        begin++;
                    }
                    if (res == "" || (end - begin + 1) < res.size()) {
                        res = s.substr(begin, end - begin + 1);
                    }
                    cout << s.substr(begin, end - begin + 1) << endl;
                    begin++;
                }
            }
        }
        return res;
    }

    // 77. Combinations
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > combs;
        vector<int> comb;
        backTrackingCombine(combs, comb, 1, n, k);
        return combs;
    }

    void backTrackingCombine(vector<vector<int> > &combs, vector<int> &comb, int start, int end, int k) {
        if (k == 0) {
        vector<int> newComb = comb;
        combs.push_back(comb);
        } else {
        for (int i = start; i <= end + 1 - k; i++) {
            comb.push_back(i);
            backTrackingCombine(combs, comb, i + 1, end, k - 1);
            comb.erase(comb.end() - 1);
        }
        }
    }

    // 78. Subsets
    vector<vector<int> > subsets(vector<int>& nums) {
        vector<vector<int> > subs;
        vector<int> sub;        
        backTrackingSubset(subs, sub, nums, 0);
        return subs;
    }

    void backTrackingSubset(vector<vector<int> > &subs, vector<int> &sub, vector<int> &nums, int start) {
        vector<int> newSub = sub;
        subs.push_back(newSub);
        for (int i = start; i < nums.size(); i++) {
        sub.push_back(nums[i]);
        backTrackingSubset(subs, sub, nums, i + 1);
        sub.erase(sub.end() - 1);
        }
    }

    // 79. Word Search
    bool exist(vector<vector<char> > & board, string word) {
        for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board[i].size(); j++)
            if (backTrackingExist(board, i, j, word))
            return true;
        return false;
    }

    bool backTrackingExist(vector<vector<char> > &board, int startX, int startY, string &word) {
        if (word.size() == 0) {
        return true;
        } else if (startX < 0 || startY < 0 || startX >= board.size() || startY >= board[0].size() || board[startX][startY] != word[0]) {
        return false;
        } else {
        string newStr = word.substr(1, word.size() - 1);
        board[startX][startY] += 100;
        bool res = backTrackingExist(board, startX + 1, startY, newStr) || backTrackingExist(board, startX - 1, startY, newStr) || backTrackingExist(board, startX, startY + 1, newStr) || backTrackingExist(board, startX, startY - 1, newStr);
        board[startX][startY] -= 100;
        return res;
        }
    }

    // 80. Remove Duplicates from Sorted Array II
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();
        int end = 1, cur = 1, count = 1, nowValue = nums[0];
        while (cur < nums.size()) {
        if (nums[cur] == nowValue) {
            count++;
        } else {
            nowValue = nums[cur];
            count = 1;
        }
        if (count <= 2) {
            nums[end++] = nowValue;
        }
        cur++;
        }
        return end;
    }


    void printArr(vector<int> & nums) {
        for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
        }
        cout << endl;
    }

    void printMatrix(vector<vector<int> > &matrix) {
        for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
        }
    }
    };

int main () {

    Solution solution;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    cout << solution.minWindow(s, t) << endl;
    // cout << boolalpha << s.exist(board, "SEE") << endl;
}