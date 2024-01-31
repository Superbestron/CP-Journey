#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, c; cin >> t;
    while (t--) {
        cin >> n >> c;
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            arr[i] += i + 1;
        }
        sort(arr, arr + n);
        int cost = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            cost += arr[i];
            if (cost > c) {
                break;
            }
            ans++;
        }
        cout << ans << '\n';
    }
}
