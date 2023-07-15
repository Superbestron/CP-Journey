#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p, k, prev = 0, curr; cin >> n >> p >> k;
    double ans = 0, multiplier = 1;
    while (n--) {
        cin >> curr;
        ans += (curr - prev) * multiplier;
        prev = curr;
        multiplier += p / 100.0;
    }
    ans += (k - curr) * multiplier;
    cout << fixed << setprecision(7) << ans;
}