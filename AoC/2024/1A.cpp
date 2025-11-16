#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Simple sorting.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y;
    vi a, b;
    while (cin >> x >> y) {
        a.push_back(x);
        b.push_back(y);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int ans = 0;
    for (int i = 0; i < a.size(); i++) ans += abs(a[i] - b[i]);
    cout << ans << '\n';
}
