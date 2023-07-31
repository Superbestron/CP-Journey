#include <bits/stdc++.h>

using namespace std;

long long arr[10][19][2][2];
string hill;

long long dp(int prev, int pos, bool is_rising, bool is_lower) {
    if (pos == hill.size()) return 1;
    long long& ans = arr[prev][pos][is_rising][is_lower];
    if (ans != -1) return ans;
    ans = 0;
    if (is_rising) {
        if (is_lower) {
            for (int i = 0; i <= 9; i++) {
                ans += dp(i, pos + 1, i >= prev, true);
            }
        } else {
            for (int i = 0; i <= hill[pos] - '0'; i++) {
                ans += dp(i, pos + 1, i >= prev, i < hill[pos] - '0');
            }
        }
    } else {
        if (is_lower) {
            for (int i = 0; i <= prev; i++) {
                ans += dp(i, pos + 1, false, true);
            }
        } else {
            // cannot exceed prev
            for (int i = 0; i <= min(prev, hill[pos] - '0'); i++) {
                ans += dp(i, pos + 1, false, i < hill[pos] - '0');
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> hill;
    bool rising = true, is_hill_no = true;
    memset(arr, -1, sizeof arr);

    for (int i = 1; i < hill.size(); i++) {
        if (hill[i] < hill[i - 1]) rising = false;
        if (!rising && hill[i] > hill[i - 1]) {
            is_hill_no = false;
            break;
        }
    }
    // extra answer consisting of all 0s
    if (is_hill_no) cout << dp(0, 0, true, false) - 1;
    else cout << -1;
}