#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, ans = 0; cin >> n >> m;
    int arr[m][2];
    for (int i = 0; i < m; i++) {
        cin >> arr[i][0] >> arr[i][1];
    }
    for (int i = 0; i < 1 << n; i++) {
        bool pass = true;
        for (int j = 0; j < m; j++) {
            if (i & 1 << (arr[j][0] - 1) && i & 1 << (arr[j][1] - 1)) {
                pass = false;
                break;
            }
        }
        if (pass) ans++;
    }
    cout << ans;
}
