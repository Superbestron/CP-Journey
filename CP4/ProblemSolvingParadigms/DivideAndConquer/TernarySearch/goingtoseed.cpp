#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    int lo = 1, hi = N, left, right, mid, left_mid, right_mid;
    while (hi > lo) {
        mid = (lo + hi) / 2;
        left_mid = (lo + mid) / 2;
        right_mid = (mid + hi) / 2;
        cout << "Q " << lo << ' ' << left_mid << ' ' << right_mid << ' ' << hi << '\n';
        cout.flush();
        cin >> left >> right;
        if (left == 0 && right == 0) {
            hi = right_mid - 1;
            lo = left_mid + 1;
        } else if (left == 1) {
            hi = min(right_mid - 1, left_mid);
        } else {
            lo = max(left_mid + 1, right_mid);
        }
    }
    cout << "A " << lo;
}