#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vi match, vis;
vector<vi> AL;
unordered_set<int> LE, U, R, Z;

int aug(int L) {
    if (vis[L]) return 0;
    vis[L] = 1;
    for (auto& R : AL[L]) {
        if ((match[R] == -1 || aug(match[R]))) {
            match[L] = R;
            match[R] = L;
            return 1;
        }
    }
    return 0;
}

bool connected_to_u(int i) {
    if (vis[i]) return false;
    vis[i] = 1;
    if (U.count(i)) return true;
    if (LE.count(i)) return connected_to_u(match[i]);
    return any_of(AL[i].begin(), AL[i].end(), connected_to_u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, a, b, idx = 0;
    cin >> m;
    AL.assign(2000, {});
    unordered_map<int, int> id_to_vertex, vertex_to_id;
    int MCBM = 0, idx_1009 = -1;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        if (!id_to_vertex.count(a)) {
            id_to_vertex[a] = idx;
            if (a == 1009) idx_1009 = idx;
            vertex_to_id[idx] = a;
            LE.insert(idx++);
        }
        if (!id_to_vertex.count(b)) {
            id_to_vertex[b] = idx;
            R.insert(idx);
            vertex_to_id[idx++] = b;
        }
        int a_idx = id_to_vertex[a], b_idx = id_to_vertex[b];
        AL[a_idx].push_back(b_idx);
        AL[b_idx].push_back(a_idx);
    }
    match.assign(idx, -1);
    if (idx_1009 != -1) {
        // greedily match with 1009 first to ensure that 1009 will always be matched if possible
        vis.assign(idx, 0);
        MCBM += aug(idx_1009);
    }
    for (int i : LE) {
        if (i == idx_1009) continue;
        vis.assign(idx, 0);
        MCBM += aug(i);
    }
    cout << MCBM << '\n';
    for (int i = 0; i < idx; i++) {
        if (match[i] == -1 && LE.count(i)) U.insert(i);
    }
    for (int i = 0; i < idx; i++) {
        vis.assign(idx, 0);
        if (connected_to_u(i)) Z.insert(i);
    }
    unordered_set<int> L_Z, RnZ, ans;
    for (int i : LE) if (!Z.count(i)) L_Z.insert(i);
    for (int i : R) if (Z.count(i)) RnZ.insert(i);
    for (int i : L_Z) ans.insert(i);
    for (int i : RnZ) ans.insert(i);
    for (int i : ans) cout << vertex_to_id[i] << '\n';
}