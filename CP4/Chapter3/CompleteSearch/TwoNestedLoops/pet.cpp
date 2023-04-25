#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int val, max_idx = -1, max = 0;
    for (int i = 1; i <= 5; i++) {
        int sum = 0, count = 4;
        while (count--) {
            cin >> val;
            sum += val;
        }
        if (sum > max) {
            max_idx = i;
            max = sum;
        }
    }
    cout << max_idx << ' ' << max << '\n';
}
