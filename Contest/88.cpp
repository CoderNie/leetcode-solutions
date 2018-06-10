#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <climits>

using namespace std;

class Solution {
public:
  string shiftingLetters(string S, vector<int>& shifts) {
    for (int j = shifts.size() - 2; j >= 0; j--) {
      shifts[j] = (shifts[j] % 26 + shifts[j + 1] % 26) % 26;
    }
    for (int i = 0; i < S.size(); i++) {
      int sum = S[i] + shifts[i];
      if (sum > 122) {
        sum = (sum - 97) % 26 + 97;
      }
      S[i] = (char)sum;
    }
    return S;
  }

  int maxDistToClosest(vector<int>& seats) {
    int maxZero = 0;
    bool endEmpty = false;
    int sum = 0;
    for (int i = 0; i < seats.size(); i++) {
      if (seats[i] == 0) {
        if ((sum == 0 && i == 0) || (i == seats.size() - 1)) {
          endEmpty = true;
        }
        sum++;
        if (endEmpty) {
          maxZero = max(sum, maxZero);
        } else {
          maxZero = max((sum + 1) / 2, maxZero);
        }
      } else {
        sum = 0;
        endEmpty = false;
      }
    }
    return maxZero;    
  }

};

int main() {
  Solution s;
  vector<int> arr = {3, 5, 360};
  // cout << s.maxDistToClosest(arr) << endl;
  cout << s.shiftingLetters("abc", arr) << endl;
  return 0;
}
