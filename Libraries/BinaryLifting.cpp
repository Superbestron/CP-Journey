#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;

int n, q, l, timer;
vi tin, tout, L;
vector<vi> AL, up;

void dfs(int v, int p, int h) {
    L[v] = h;
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; i++) up[v][i] = up[up[v][i - 1]][i - 1]; // Jump halfway first and then jump another time
    for (int u : AL[v]) if (u != p) dfs(u, v, h + 1);
    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = l; i >= 0; i--) if (!is_ancestor(up[u][i], v)) u = up[u][i];
    return up[u][0];
}

int getKthAncestor(int node, int k) {
    if (L[node] < k) return -1;
    int left = k;
    int u = node;
    while (left > 1) {
        int jump = floor(log2(left));
        u = up[u][jump];
        left -= pow(2, jump);
    }
    if (left == 1) return up[u][0];
    else return u;
}

void preprocess(int root) {
    tin.assign(n, 0);
    tout.assign(n, 0);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vi(l + 1));
    AL.assign(n, vi());
    dfs(root, root, 0);
}

int main() {
    cin >> n;
    vi parent(n);
    for (int& i : parent) cin >> i;
    AL.assign(n, vi());
    for (int i = 0; i < n; i++) {
        if (parent[i] == -1) continue;
        AL[parent[i]].push_back(i);
    }
    preprocess(0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int node, k; cin >> node >> k;
        cout << getKthAncestor(node, k) << ' ';
    }
    cout << '\n';
}
