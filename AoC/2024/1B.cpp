#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Simple Hashmap.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y;
    vi a;
    map<int, int> mp;
    while (cin >> x >> y) {
        a.push_back(x);
        mp[y]++;
    }
    int ans = 0;
    for (int i = 0; i < a.size(); i++) ans += a[i] * mp[a[i]];
    cout << ans << '\n';
}
