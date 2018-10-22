#include <vector>
#include <iostream>
// #include <pair>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    int sum;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void input(vector<int> &arr) {
    int i = 0;
    do {
        arr.push_back(0);
		cin >> arr[i];
        i++;
    } while(cin.get() != '\n');
}

int indexOf(vector<int> &arr, int begin, int end, int key) {
    for (int i = begin; i <= end; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

TreeNode* createTree(vector<int> &preArr, int pBegin, int pEnd, vector<int> &inArr, int iBegin, int iEnd) {
    if (pBegin > pEnd) {
        return NULL;
    } else if (pBegin == pEnd) {
        TreeNode* node = new TreeNode(preArr[pBegin]);
        return node;
    } else {
        TreeNode* node = new TreeNode(preArr[pBegin]);
        int index = indexOf(inArr, iBegin, iEnd, preArr[pBegin]);
        int leftSize = index - iBegin;
        int rightSize = iEnd - index;
        node->left = createTree(preArr, pBegin + 1, pBegin + leftSize, inArr, iBegin, index - 1);
        node->right = createTree(preArr, pBegin + leftSize + 1, pEnd, inArr, index + 1, iEnd);
        return node;
    }
}

void inOrder(TreeNode *root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->sum << " ";
        inOrder(root->right);
    }
}
int getSum(TreeNode *root) {
    if (root == NULL) {
        return 0;
    } else if (root->left == NULL && root->right == NULL) {
        return root->val;
    } else {
        root->sum = getSum(root->left) + getSum(root->right);
        return (root->sum + root->val);
    }
}

// int main () {
//     vector<int> preArr, inArr;
//     input(preArr);
//     input(inArr);
//     TreeNode *root = createTree(preArr, 0, preArr.size() - 1, inArr, 0, inArr.size() - 1);
//     getSum(root);
//     inOrder(root);
//     cout << endl;
// }


int main() {
    int n, w, h;
    vector<pair<long, pair<int, int> > > pairs;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            continue;
        }
        for (int i = 0; i < n; i++) {
            cin >> w >> h;
            pairs.push_back({w * h, {w, h}});
        }
        sort(pairs.begin(), pairs.end());
        // for (int i = 0; i < n; i++) {
        //     cout << pairs[i].second.first << "," << pairs[i].second.second << "  ";
        // }
        int res = 0;
        for (int j = 0; j < n; j++) {
            int now = 1;
            w = pairs[j].second.first;
            h = pairs[j].second.second;
            for (int i = j + 1; i < n; i++) {
                if (pairs[i].second.first >= w && pairs[i].second.second >= h) {
                    w = pairs[i].second.first;
                    h = pairs[i].second.second;
                    now++;
                }
            }
            res = max(res, now);
        }
        cout << res << endl;
    }
}
