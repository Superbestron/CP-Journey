#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        cout << ceil(1.0 * (n - 1) / k) + 1 << '\n';
    }
}