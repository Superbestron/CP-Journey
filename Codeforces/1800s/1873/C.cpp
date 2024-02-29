#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    vector<vector<int>> pts(10, vector<int>(10));
    for (int i = 0; i < 5; i++) {
        for (int j = 0 + i; j < 10 - i; j++) {
            pts[j][i] = i + 1;
            pts[j][10 - i - 1] = i + 1;
        }
        for (int j = 0 + i; j < 10 - i; j++) {
            pts[i][j] = i + 1;
            pts[10 - i - 1][j] = i + 1;
        }
    }
    while (t--) {
        vector<string> v(10);
        int sum = 0;
        for (auto& s : v) cin >> s;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                char c = v[i][j];
                if (c != 'X') continue;
                sum += pts[i][j];
            }
        }
        cout << sum << '\n';
    }
}