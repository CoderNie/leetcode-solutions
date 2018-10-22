#include <queue>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <ctime>
#include <climits>
#include <cstring>

using namespace std;

class Solution {
public:
    void reverseWord(string &str, int begin, int end) {
        char temp;
        while (begin < end) {
            temp = str[begin];
            str[begin] = str[end];
            str[end] = temp;
            begin++;
            end--;
        }
    }
    string ReverseSentence(string str) {
        string res = str;
        reverseWord(res, 0, res.size() - 1);
        int begin = 0, end = 0;
        while (end < res.size()) {
            if (res[end] == ' ') {
                reverseWord(res, begin, end - 1);
                begin = end + 1;
            }
            end++;
        }
        if (begin < end)
            reverseWord(res, begin, end - 1);
        return res;
    }
    void printArr(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++)
            cout << nums[i] << ", ";
        cout << endl;
    }
    bool IsContinuous( vector<int> numbers ) {
        sort(numbers.begin(), numbers.end());
        int i = 0, balance = 0;
        while (numbers[i] == 0) {
            balance++;
            i++;
        }
        printArr(numbers);
        while (i + 1 < numbers.size()) {
            if (numbers[i + 1] == numbers[i]) {
                return false;
            } else if (numbers[i + 1] - 1 == numbers[i]) {
                i++;
            } else if (balance > 0) {
                numbers[i]++;
                balance--;
            } else {
                return false;
            }
        }
        return true;
    }
};

int main() {
    // vector<int> arr;
    // int i =0;
    // while((cin.peek()!=EOF)&&(cin.peek()!='\n')){
    //     arr.push_back(0);
	// 	cin >> arr[i];
    //     i++;
	// }
    // for (int j = 0; j < i; j++) {
    //     cout << arr[j] << " ";
    // }
    string s = "hello!qwkje!#qwe!";
    vector<string> arr = split(s, "!");
    cout << arr[0] << endl;
}