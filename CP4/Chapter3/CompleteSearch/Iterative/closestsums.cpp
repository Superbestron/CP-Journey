#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1, n, m, q;
    while (cin >> n) {
        int arr[n];
        vector<int> pairs;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            for (int j = 0; j < i; j++) pairs.push_back(arr[j] + arr[i]);
        }
        sort(pairs.begin(), pairs.end());
        cin >> m;
        cout << "Case " << t++ << ':' << '\n';
        while (m--) {
            cin >> q; cout << "Closest sum to " << q << " is ";
            auto upper = lower_bound(pairs.begin(), pairs.end(), q);
            if ((*upper) == q) cout << q;
            else if (upper == pairs.end()) cout << *(upper - 1);
            else if (upper == pairs.begin()) cout << *upper;
            else {
                if (abs(q - *(upper - 1)) > abs(*upper - q)) cout << *upper;
                else cout << *(upper - 1);
            }
            cout << ".\n";
        }
    }
}
