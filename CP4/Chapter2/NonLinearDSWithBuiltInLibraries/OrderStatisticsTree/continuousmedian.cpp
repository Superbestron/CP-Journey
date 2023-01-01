#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;
// use less_equal instead of less to handle duplicates
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ost;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, val; cin >> t;
    while (t--) {
        ost t1;
        cin >> n;
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            cin >> val;
            t1.insert(val);
            if (i % 2 == 0) { // even
                auto it = t1.find_by_order(i / 2);
                ans += (*it + *(--it);) / 2;
            } else { // odd
                ans += *t1.find_by_order(i / 2);
            }
        }
        cout << ans << '\n';
    }
}
