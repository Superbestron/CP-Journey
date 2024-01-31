#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> v(n);
        for (int& i : v) cin >> i;
        sort(v.begin(), v.end());
        int sum = 1;
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                sum *= (1 + v[i]);
            } else sum *= v[i];
        }
        cout << sum << '\n';
    }
}