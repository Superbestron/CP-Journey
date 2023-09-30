#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    while (t--) {
        cin >> n;
        int arr[n], neg_count = 0, smallest = 1e9;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            sum += abs(arr[i]);
            smallest = min(smallest, abs(arr[i]));
            if (arr[i] <= 0) {
                neg_count++;
            }
        }
        if (neg_count & 1) cout << sum - 2 * smallest << '\n';
        else cout << sum << '\n';
    }
}
