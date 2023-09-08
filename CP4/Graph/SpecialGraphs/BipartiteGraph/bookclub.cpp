#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi match, vis;                                   // global variables
vector<vi> AL;

int Aug(int L) {
    if (vis[L]) return 0;                          // L visited, return 0
    vis[L] = 1;
    for (auto &R : AL[L])
        if ((match[R] == -1) || Aug(match[R])) {
            match[R] = L;                              // flip status
            return 1;                                  // found 1 matching
        }
    return 0;                                      // no matching
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, a, b;
    cin >> N >> M;
    AL.assign(2 * N, vector<int>());
    while (M--) {
        cin >> a >> b;
        AL[a].push_back(b + N);
        AL[b + N].push_back(a);
    }
    match.assign(2 * N, -1);
    int MCBM = 0;     // for each free vertex
    for (int i = 0; i < N; i++) {                        // (in random order)
        vis.assign(N, 0);                        // reset first
        MCBM += Aug(i);                              // try to match f
    }
    if (MCBM == N) cout << "YES";
    else cout << "NO";
}