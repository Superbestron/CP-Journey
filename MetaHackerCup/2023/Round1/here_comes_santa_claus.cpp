#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, N;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> N;
        vector<int> v(N);
        for (int &j : v) cin >> j;
        sort(v.begin(), v.end());
        double ans;
        if (N == 5) {
            ans = max((double) (v[N - 1] + v[N - 3]) / 2 - (double) (v[1] + v[0]) / 2,
                      (double) (v[N - 1] + v[N - 2]) / 2 - (double) (v[2] + v[0]) / 2);
        } else {
            ans = (double) (v[N - 1] + v[N - 2]) / 2 - double(v[1] + v[0]) / 2;
        }

        cout << fixed << setprecision(7) << "Case #" << i << ": " << ans << '\n';
    }
}
