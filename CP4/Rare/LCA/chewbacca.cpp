#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll x, y, N, K, Q;

// draw out the tree to observe this fact!
ll parent(ll u) {
    ll x = u / K;
    if ((u % K) == 0 || (u % K) == 1) return x;
    return x + 1;
}

ll depth(ll u) {
    ll num = 1, depth = 0;
    while (u - num >= 1) {
        u -= num;
        depth++;
        num *= K;
    }
    return depth;
}

ll d_u, d_v;

ll lca(ll u, ll v) {
    ll depth_u = d_u, depth_v = d_v;
    while (depth_u < depth_v){
        v = parent(v);
        depth_v--;
    }
    while (depth_v < depth_u){
        u = parent(u);
        depth_u--;
    }
    while (u != v){
        u = parent(u);
        v = parent(v);
        depth_u--;
        depth_v--;
    }
    return depth_u;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> x >> y;
        if (K == 1) {
            cout << llabs(x - y) << '\n';
            continue;
        }
        d_u = depth(x);
        d_v = depth(y);
        ll num = lca(x, y);
        cout << d_u + d_v - 2 * num << '\n';
    }
}