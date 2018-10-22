#include <vector>
#include <iostream>
// #include <pair>
#include <algorithm>
using namespace std;

int main() {
    int n, w, h;
    cin >> n;
    if (n == 0) {
        cout << 0 << endl;
    }
    int nowW = 0, nowH = 0, res = 0;
    for (int i = 0; i < n; i++) {
        cin >> w >> h;
        if (w >= nowW && h >= nowH) {
            res++;
            nowW = w;
            nowH = h;
        }
    }
    cout << res << endl;
}
