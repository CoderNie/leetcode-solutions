#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
class Solution {
public:
    TreeNode* outRes;
    void traverse(TreeNode* root, int *cnt, int k) {
        if (root != NULL) {
            traverse(root->left, cnt, k);
            *cnt = *cnt + 1;
            if (*cnt == k) {
                outRes = root;
                return;
            }
            traverse(root->right, cnt, k);
        }
    }
    TreeNode* KthNode(TreeNode* pRoot, int k) {
        int *cnt;
        *cnt = 0;
        traverse(pRoot, cnt, k);
        return outRes;
    }
    int R;
    int C;
    vector<vector<bool>> isPassed;
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        isPassed = {};
        R = rows;
        C = cols;
        int length = strlen(str);
        if (length == 0)
            return true;
        for (int i = 0; i < rows; i++) {
            isPassed.push_back({});
            for (int j = 0; j < cols; j++) {
                isPassed[i].push_back(false);
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (isOK(i, j, matrix, str, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool isOK(int x, int y, char* matrix, char* str, int strI) {
        if (strI == strlen(str))
            return true;
        if (x >= 0 && x < R && y >= 0 && y < C && !isPassed[x][y] && matrix[x][y] == str[strI]) {
            isPassed[x][y] = true;
            if (isOK(x + 1, y, matrix, str, strI + 1) || isOK(x - 1, y, matrix, str, strI + 1)
               || isOK(x, y + 1, matrix, str, strI + 1) || isOK(x, y - 1, matrix, str, strI + 1)) {
                return true;
            } else {
                isPassed[x][y] = false;
                return false;
            }
        } else {
            return false;
        }
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(0);
    root->right = new TreeNode(3);
    Solution s;
    TreeNode* res = s.KthNode(root, 1);
    cout << res->val << endl;
    vector<int> arr;
    arr.insert(arr.begin(), 3);
    arr.insert(arr.begin(), 4);
    cout << arr[0] << endl;
}