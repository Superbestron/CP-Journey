#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        int xor_sum_a = 0, or_sum_b = 0;
        vector<int> a(n), b(m);
        for (int& i : a) {
            cin >> i;
            xor_sum_a ^= i;
        }
        for (int& i : b) {
            cin >> i;
            or_sum_b |= i;
        }
        if (n & 1) {
            cout << xor_sum_a << ' ' << (xor_sum_a | or_sum_b)<< '\n';
        } else {
            int tmp = xor_sum_a & or_sum_b;
            int mini = xor_sum_a ^ tmp;
            cout << mini << ' ' << xor_sum_a << '\n';
        }
    }
}

