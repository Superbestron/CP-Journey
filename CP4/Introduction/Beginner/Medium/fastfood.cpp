#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, m, k; cin >> t;
    while (t--) {
        int total = 0;
        cin >> n >> m;
        vector<vector<int>> v(n);
        vector<int> values(n), stickers(m);

        for (int i = 0; i < n; i++) {
            cin >> k;
            v[i].resize(k);
            for (int& j : v[i]) {
                cin >> j;
                j--;
            }
            cin >> values[i];
        }

        for (int& i : stickers) cin >> i;
        for (int i = 0; i < n; i++) {
            int mini = stickers[v[i][0]];
            for (int j : v[i]) mini = min(mini, stickers[j]);
            total += mini * values[i];
        }
        cout << total << endl;
    }
}