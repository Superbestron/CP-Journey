#include <bits/stdc++.h>
#include "../../../Libraries/PrimalityCheck.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;

int t, n, a, b;

inline void solve() {
    cin >> n >> a >> b;
    for (int i = 0; i < 2 * n; i++) cout << 1 << ' ';
    cout << b << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    sieve(1000000);
    for (int t = 1; t <= T; t++) {
        printf("Case #%d: ", t);
        solve();
        cout << '\n';
    }
}
