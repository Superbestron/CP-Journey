#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;

int N, M, a, b, ans, OK;
set<pair<int, int>> m;

void backtrack(int rw, int ld, int rd, int col) {
    if (rw == OK) {
        ans++;
        return;
    }
    int pos = OK & (~(rw | ld | rd));
    while (pos) {
        int p = LSOne(pos);
        int j = __builtin_ctz(p);
        pos -= p;
        if (!m.count({j, col})) backtrack(rw | p, (ld | p) << 1, (rd | p) >> 1, col + 1);
    }
}

int main() {
    while (cin >> N >> M && !(N == 0 && M == 0)) {
        m.clear();
        ans = 0, OK = (1 << N) - 1;
        for (int i = 0; i < M; i++) {
            cin >> a >> b;
            m.emplace(a, b);
        }
        backtrack(0, 0, 0, 0);
        cout << ans << '\n';
    }
}