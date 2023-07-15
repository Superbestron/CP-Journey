#include <iostream>
#include <unordered_map>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val, ans = INT32_MAX; cin >> n;
    bool unique = true;
    // language: most recent index
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++) {
        cin >> val;
        if (m.count(val)) {
            unique = false;
            ans = min(ans, i - m[val]);
        }
        m[val] = i;
    }
    if (unique) cout << n;
    else cout << ans;
}