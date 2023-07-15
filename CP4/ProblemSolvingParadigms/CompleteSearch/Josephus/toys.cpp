#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, K, ans = 0; cin >> T >> K;
    for (int i = 1; i < T; i++) {
        ans = (ans + K) % (i + 1);
    }
    cout << ans;
}