#include <bits/stdc++.h>

using namespace std;

int n, weights[1000], memo[1001][2001];

int dp(int weight, int curr) {
    int &ans = memo[weight][curr];
    if (ans != -1) return ans;
    if (weight == n || curr > 1000) return ans = abs(1000 - curr);
    return ans = min(dp(weight + 1, curr), dp(weight + 1, curr + weights[weight]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    memset(memo, -1, sizeof memo);
    int diff = dp(0, 0);
    if (memo[n][1000 + diff] != -1) cout << 1000 + diff;
    else cout << 1000 - diff;
}