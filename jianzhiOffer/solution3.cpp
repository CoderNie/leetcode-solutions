#include <queue>
#include <vector>
#include <map>
#include <set>
#include <stack>

#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <ctime>
#include <climits>

using namespace std;


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    int TreeDepth(TreeNode* pRoot) {
        if (pRoot == NULL) return 0;
        queue<pair<TreeNode*, int> > bfsQueue;
        bfsQueue.push({pRoot, 1});
        int res = 0;
        while (!bfsQueue.empty()) {
            TreeNode *nowNode = bfsQueue.front().first;
            int nowDepth = bfsQueue.front().second;
            res = nowDepth;
            bfsQueue.pop();
            if (nowNode->left != NULL)
                bfsQueue.push({nowNode->left, nowDepth + 1});
            if (nowNode->right != NULL)
                bfsQueue.push({nowNode->right, nowDepth + 1});
        }
        return res;
    }
};

int main() {
    TreeNode *root = new TreeNode(0);
    root->left = new TreeNode(1);
    root->left->left = new TreeNode(2);
    Solution s;
    cout << s.TreeDepth(root) << endl;
}