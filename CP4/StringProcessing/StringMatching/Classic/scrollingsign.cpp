#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, k, w; cin >> t;
    string s;
    while (t--) {
        cin >> k >> w;
        vector<string> v(w);
        int ans = k * w;
        for (int i = 0; i < w; i++) cin >> v[i];
        for (int i = 1; i < w; i++) {
            for (int j = 0; j < k; j++) {
                string temp = v[i - 1].substr(j);
                if (v[i].find(temp) == 0) {
                    ans -= temp.size();
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
}