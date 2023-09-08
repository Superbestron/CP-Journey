#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;

int T, V, E, numIS, MIS;
long long AM[64];

void backtrack(int u, long long mask, int depth) {
    if (!mask) {
        ++numIS;
        MIS = max(MIS, depth);
        return;
    }
    long long m = mask;
    while (m) {
        long long two_pow_v = LSOne(m);
        int v = __builtin_ctzl(two_pow_v);
        m -= two_pow_v;
        if (v < u) continue;
        backtrack(v + 1, mask & ~AM[v], depth + 1);
    }
}

int main() {
    cin >> T;
    while (T--) {
        numIS = 0, MIS = 0;
        cin >> V >> E;
        memset(AM, 0, sizeof AM);
        for (int u = 0; u < V; u++) AM[u] = (1LL << u);
        while (E--) {
            int a, b; scanf("%d %d", &a, &b);
            AM[a] |= (1LL << b);
            AM[b] |= (1LL << a);
        }
        backtrack(0, (1LL << V) - 1, 0);
        printf("%d\n%d\n", numIS, MIS);
    }
}