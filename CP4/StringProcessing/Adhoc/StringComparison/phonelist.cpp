#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    while (t--) {
        cin >> n;
        string arr[n];
        for (int i = 0; i < n; i++) cin >> arr[i];
        sort(arr, arr + n);
        bool consistent = true;
        for (int i = 1; i < n; i++) {
            if (arr[i].find(arr[i - 1]) == 0) {
                consistent = false;
                break;
            }
        }
        if (consistent) cout << "YES\n";
        else cout << "NO\n";
    }
}