#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int P, arr[12]; cin >> P;
    for (int i = 1; i <= P; i++) {
        int ans = 0;
        cin >> i;
        for (int& j : arr) {
            cin >> j;
        }
        for (int j = 1; j < 11; j++) {
            for (int k = j; k < 11; k++) {
                bool can = true;
                int start = arr[j - 1], end = arr[k + 1];
                for (int l = j; l <= k; l++) {
                    if (arr[l] <= start || arr[l] <= end) {
                        can = false; break;
                    }
                }
                if (can) ans++;
            }
        }
        cout << i << ' ' << ans << '\n';
    }
}