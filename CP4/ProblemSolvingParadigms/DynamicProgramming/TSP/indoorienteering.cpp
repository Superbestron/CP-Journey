#include <bits/stdc++.h>
#define LSOne(S) (S & -(S))
using namespace std;
typedef long long ll;

ll n, L, AM[14][14];
int OK;
unordered_set<ll> costs;
bool can = false;

void backtrack(int u, int mask, ll cost, int c, bool left) {
    if (mask == 0) {
        if (left) {
            costs.insert(cost + AM[u][c + 1]);
        } else {
            if (costs.count(L - (AM[u][c + 1] + cost))) {
                can = true;
            }
        }
        return;
    }
    int m = mask;
    while (m) {
        int two_pow_v = LSOne(m);
        int v = __builtin_ctz(two_pow_v) + 1;
        backtrack(v, mask ^ two_pow_v, cost + AM[u][v], c, left);
        m -= two_pow_v;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> L;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> AM[i][j];
        }
    }
    OK = (1 << (n - 1)) - 1;
    for (int c = 0; c < n - 1; c++) { // 0 means city second city
        for (int l = 0; l < (OK); l++) {
            if (l & (1 << c)) continue; // centre
            int bits = 0;
            int mask = l;
            while (mask > 0) {
                if (mask & 1) bits++;
                mask >>= 1;
            }
            if (bits != (n - 1) / 2) continue;
            int r = OK - l - (1 << c);
            costs.clear();
            backtrack(0, l, 0, c, true);
            backtrack(0, r, 0, c, false);
            if (can) goto done;
        }
    }
    done:
    if (can) cout << "possible";
    else cout << "impossible";
}