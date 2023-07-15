#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, val;
    while (cin >> n >> m && n != 0 && m != 0) {
        int ans = 0;
        unordered_set<int> s;
        while (n--) {
            cin >> val;
            s.insert(val);
        }
        while (m--) {
            cin >> val;
            if (s.count(val) == 1) ans++;
        }
        cout << ans << endl;
    }
}