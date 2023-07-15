#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, d, n, val, start = 6, ans = 0; cin >> l >> d >> n;
    vector<int> v;
    while (n--) {
        cin >> val;
        v.push_back(val);
    }
    v.push_back(l - 6 + d); // simulate a fake bird
    sort(v.begin(), v.end());
    for (int limit : v) {
        while (start + d <= limit) {
            ans++;
            start += d;
        }
        start = limit + d;
    }
    cout << ans;
}