#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, c, ans = 0;
    long long x;
    cin >> n >> m >> a >> c >> x;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        x = (a * x + c) % m;
        v.push_back(x);
    }
    for (int i : v) {
        int low = 0, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (v[mid] == i) {
                ans++;
                break;
            } else if (v[mid] < i) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    cout << ans;
}