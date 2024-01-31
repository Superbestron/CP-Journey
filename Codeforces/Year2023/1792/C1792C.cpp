#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, val, left, right; cin >> t;
    while (t--) {
        cin >> n; int pos[n + 1];
        for (int i = 0; i < n; i++) {
            cin >> val;
            pos[val] = i;
        }
        left = (n + 1) / 2, right = (n + 2) / 2;
        while (left > 0 && (left == right || pos[left] < pos[left + 1] && pos[right - 1] < pos[right])) {
            left--; right++;
        }
        cout << left << '\n';
    }
}
