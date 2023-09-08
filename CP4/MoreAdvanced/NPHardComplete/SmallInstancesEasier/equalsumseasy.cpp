#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, N;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N;
        cout << "Case #" << tc << ':' << '\n';
        bool found = false;
        vector<int> nums(N);
        unordered_map<int, int> mp;
        for (int i = 0; i < N; i++) cin >> nums[i];
        for (int i = 1; i < (1 << N); i++) {
            int m = i;
            int sum = 0;
            while (m) {
                int mask = LSOne(m);
                int cnt = __builtin_ctz(mask);
                sum += nums[cnt];
                m -= mask;
            }
            if (mp.count(sum)) {
                int m1 = mp[sum];
                while (m1) {
                    int mask = LSOne(m1);
                    int cnt = __builtin_ctz(mask);
                    cout << nums[cnt] << ' ';
                    m1 -= mask;
                }
                cout << '\n';
                int m2 = i;
                while (m2) {
                    int mask = LSOne(m2);
                    int cnt = __builtin_ctz(mask);
                    cout << nums[cnt] << ' ';
                    m2 -= mask;
                }
                cout << '\n';
                found = true;
                break;
            }
            mp[sum] = i;
        }
        if (!found) cout << "Impossible\n";
    }
}

