#include <bits/stdc++.h>
using namespace std;

vector<vector<tuple<int, int>>> AL;
vector<vector<tuple<int, int>>> children;
vector<int> vis;
vector<bool> lamps;
vector<int> dist;
vector<vector<int>> memo;
int N, S, a, b, d, L, l;

void dfs(int u) {
    vis[u] = true;
    for (auto& [v, w] : AL[u])
        if (!vis[v]) {
            children[u].emplace_back(v, w);                  // now u<->v becomes u->v
            dist[v] = dist[u] + w;
            dfs(v);
        }
}

int MVC(int u, int flag) {
    int& ans = memo[u][flag];
    if (ans != -1) return ans;
    if (lamps[u]) {
        ans = 0;
        for (auto &[v, w]: children[u]) {
            if (dist[u] * 2 >= S) continue;
            ans += min(MVC(v, 1), MVC(v, 0));
        }
    } else {
        if (!flag) { // take all its children
            ans = 0;
            for (auto& [v, w] : children[u]) {
                if (dist[u] * 2 >= S) continue;
                ans += MVC(v, 1);
            }
        } else {
            ans = 1;
            for (auto &[v, w]: children[u]) {
                if (dist[u] * 2 >= S) continue;
                ans += min(MVC(v, 1), MVC(v, 0));
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> S;
    AL.assign(N, {});
    children.assign(N, {});
    memo.assign(N, vector<int>(2, -1));
    lamps.assign(N, false);
    vis.assign(N, false);
    dist.assign(N, 0);
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b >> d;
        a--; b--;
        AL[a].emplace_back(b, d);
        AL[b].emplace_back(a, d);
    }
    dfs(0);
    cin >> L;
    for (int i = 0; i < L; i++) {
        cin >> l;
        l--;
        lamps[l] = true;
    }
    cout << min(MVC(0, 1), MVC(0, 0));
}

