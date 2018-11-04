#include <map>
#include <queue>
#include <stack>
#include <set>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> nums;
        int a, b;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                b = nums.top();
                nums.pop();
                a = nums.top();
                nums.pop();
                if (tokens[i] == "+") {
                    nums.push(a + b);
                } else if (tokens[i] == "-") {
                    nums.push(a - b);
                } else if (tokens[i] == "*") {
                    nums.push(a * b);
                } else {
                    nums.push(a / b);
                }
            } else {
                nums.push(atoi(tokens[i].c_str()));
            }
        }
        return nums.top();
    }
};

int main () {
    vector<string> arr = {"4", "13", "5", "/", "+"};
    Solution s;
    cout << s.evalRPN(arr) << endl;
}