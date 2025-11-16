#include <bits/stdc++.h>
#include "../../../Libraries/UFDS.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;

int n;

inline int solve() {
    cin >> n;
    vi a(n);
    for (int &i : a) cin >> i;
    vector<iii> EL;

    int ans = 0;
    for (int i = 1; i < n; i++) EL.emplace_back(abs(a[i] - a[i - 1]), i, i - 1);
    // n is my ground
    for (int i = 0; i < n; i++) EL.emplace_back(a[i], i, n);
    sort(EL.begin(), EL.end()); // sort by w, O(E log E)
    int num_taken = 0; // no edge has been taken
    UnionFind UF(n + 1); // all V are disjoint sets
    for (auto &[w, u, v] : EL) { // C++17 style
        if (UF.isSameSet(u, v)) continue; // already in the same CC
        UF.unionSet(u, v); // link them
        ++num_taken; // 1 more edge is taken
        ans = max(ans, w);
        if (num_taken == n) break; // optimization
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int ans = solve();
        printf("Case #%d: %d\n", t, ans);
    }
}
