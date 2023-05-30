#include <bits/stdc++.h>

using namespace std;

int g, m, n, t, arr[30];
long long memo[30][30][10001], win, lose;

long long choose(long long n, long long k) {
    if (k == 0) return 1;
    return (n * choose(n - 1, k - 1)) / k;
}

long long dp(int type, int count, int value) {
    if (count == n) {
        if (value == 0) return 1;
        return 0;
    }
    if ((value < 0) || (type == m)) return 0; // invalid or done
    long long &ans = memo[type][count][value];
    if (ans != -1) return ans; // was computed before
    return ans = dp(type + 1, count, value) + // ignore this type
                 dp(type + 1, count + 1, value - arr[type]); // one more of this type
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> g;
    for (int tc = 1; tc <= g; tc++) {
        cin >> m;
        memset(memo, -1, sizeof memo);
        for (int i = 0; i < m; i++) cin >> arr[i];
        cin >> n >> t;
        win = dp(0, 0, t);
        lose = choose(m, n) - win;
        cout << "Game " << tc << " -- " << win << " : " << lose << '\n';
    }
}
