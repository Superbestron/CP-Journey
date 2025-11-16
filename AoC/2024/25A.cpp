#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Very simple check to see if the lock + key size is within 5.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vector<vi> locks, keys;
    vector<string> v;
    int ans = 0;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        v.push_back(s);
        if (v.size() == 7) {
            vi nums;
            if (v[0] == "#####") { // lock
                for (int j = 0; j < 5; j++) {
                    int val = 0;
                    for (int i = 1; i < 7; i++) {
                        if (v[i][j] == '#') val++;
                    }
                    nums.push_back(val);
                }
                locks.push_back(nums);
            } else {
                for (int j = 0; j < 5; j++) {
                    int val = 0;
                    for (int i = 0; i < 6; i++) {
                        if (v[i][j] == '#') val++;
                    }
                    nums.push_back(val);
                }
                keys.push_back(nums);
            }
            v.clear();
        }
    }
    for (auto& lock : locks) {
        for (auto& key : keys) {
            bool can = true;
            for (int i = 0; i < 5; i++) {
                if (lock[i] + key[i] > 5) {
                    can = false; break;
                }
            }
            if (can) ans++;
        }
    }
    cout << ans << '\n';
}
