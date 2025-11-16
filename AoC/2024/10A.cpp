#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Typical DFS question where an edge u-v exists iff u + 1 == v. However, we can afford to do a more inefficient way
// of doing the entire DFS for each '0'

int dirs[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
int m, n;

int dfs(vector<vi>& AL, vector<string>& v, int i, int j) {
    int curr = v[i][j] - '0';
    AL[i][j] = 0;
    if (curr == 9) return 1;
    int ans = 0;
    for (auto& dir : dirs) {
        int new_i = i + dir[0];
        int new_j = j + dir[1];
        if (new_i >= 0 && new_i < m && new_j >= 0 && new_j < n) {
            int next = v[new_i][new_j] - '0';
            if (curr + 1 == next ) {
                if (AL[new_i][new_j] == -1) ans += dfs(AL, v, new_i, new_j);
            }
        }
    }
    AL[i][j] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vector<string> v;
    ll ans = 0;
    while (cin >> s) v.push_back(s);
    m = v.size(), n = v[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (v[i][j] == '0') {
                vector<vi> AL(m, vi(n, -1));
                ans += dfs(AL, v, i, j);
            }
        }
    }
    cout << ans << '\n';
}
