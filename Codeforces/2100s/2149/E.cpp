#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k, l, r;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

inline void solve() {
    cin >> n >> k >> l >> r;
    vi a(n);
    unordered_map<int, int, custom_hash> mp, mp2;
    int le = 0, le_s = 0;
    ll ans = 0;
    for (int &i : a) cin >> i;
    for (int i = 0; i < n; i++) {
        mp[a[i]]++;
        mp2[a[i]]++;
        if ((int) mp.size() == k) {
            while (le_s <= i && (int) mp.size() == k) {
                mp[a[le_s]]--;
                if (mp[a[le_s]] == 0) mp.erase(a[le_s]);
                le_s++;
            }
        }
        if ((int) mp2.size() == k + 1) {
            while (le <= i && (int) mp2.size() == k + 1) {
                mp2[a[le]]--;
                if (mp2[a[le]] == 0) mp2.erase(a[le]);
                le++;
            }
        }
        int min_len = i - le_s + 2;
        int max_len = i - le + 1;
        ans += max(0, min(max_len, r) - max(min_len, l) + 1);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
