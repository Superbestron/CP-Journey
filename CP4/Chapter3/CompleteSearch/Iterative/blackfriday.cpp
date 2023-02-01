#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, ans[6]; cin >> n;
    memset(ans, -1, sizeof ans);
    unordered_set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> a;
        if (s.count(a) == 0) {
            ans[a - 1] = i + 1;
            s.insert(a);
        } else {
            ans[a - 1] = -1;
        }
    }
    bool printed = false;
    for (int i = 5; i >= 0; i--) {
        if (ans[i] != -1) {
            cout << ans[i];
            printed = true;
            break;
        }
    }
    if (!printed) cout << "none";
}
