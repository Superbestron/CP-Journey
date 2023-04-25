#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, paint; cin >> n >> m;
    long long ans = 0;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    while (m--) {
        cin >> paint;
        ans += *lower_bound(v.begin(), v.end(), paint) - paint;
    }
    cout << ans;
}