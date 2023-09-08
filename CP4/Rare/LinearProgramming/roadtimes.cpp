#include <bits/stdc++.h>
using namespace std;

typedef double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

const DOUBLE EPS = 1e-9;
int n, r, s, d, t, dist, q;
int AM[30][30], p[30][30];
map<pair<int, int>, int> road_to_idx;

// Fun question! But use double instead of long double to avoid TLE

struct LPSolver {
    int m, n;
    VI B, N;
    VVD D;

    LPSolver(const VVD &A, const VD &b, const VD &c) :
            m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, VD(n + 2)) {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
        for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
        N[n] = -1; D[m + 1][n] = 1;
    }

    void Pivot(int r, int s) {
        double inv = 1.0 / D[r][s];
        for (int i = 0; i < m + 2; i++) if (i != r)
                for (int j = 0; j < n + 2; j++) if (j != s)
                        D[i][j] -= D[r][j] * D[i][s] * inv;
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool Simplex(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
            }
            if (D[x][s] > -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] < EPS) continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
                    (D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r]) r = i;
            }
            if (r == -1) return false;
            Pivot(r, s);
        }
    }

    DOUBLE Solve(VD &x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] < -EPS) {
            Pivot(r, n);
            if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<DOUBLE>::infinity();
            for (int i = 0; i < m; i++) if (B[i] == -1) {
                    int s = -1;
                    for (int j = 0; j <= n; j++)
                        if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
                    Pivot(i, s);
                }
        }
        if (!Simplex(2)) return numeric_limits<DOUBLE>::infinity();
        x = VD(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int idx = 0;
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            AM[u][v] = 1e9;
            p[u][v] = u;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist;
            if (dist != -1) AM[i][j] = dist;
            if (dist > 0) road_to_idx[make_pair(i, j)] = idx++;
        }
    }
    for (int k = 0; k < n; k++)                    // loop order is k->u->v
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) {
                if (AM[u][k] + AM[k][v] < AM[u][v]) {
                    AM[u][v] = AM[u][k] + AM[k][v];
                    p[u][v] = p[k][v];
                }
            }
    cin >> r;
    VVD constraints;
    VD constraints_B;
    // sum of distances * speed limit = t
    for (int i = 0; i < r; i++) {
        cin >> s >> d >> t;
        // record path
        VD v(idx), v1(idx);
        while (s != d) {
            int index = road_to_idx[make_pair(p[s][d], d)];
            v[index] = AM[p[s][d]][d];
            v1[index] = -AM[p[s][d]][d];
            d = p[s][d];
        }
        constraints.push_back(std::move(v));
        constraints.push_back(std::move(v1));
        constraints_B.push_back(t);
        constraints_B.push_back(-t);
    }
    // constraints for speed limit
    for (int i = 0; i < idx; i++) {
        VD v(idx), v1(idx);
        v[i] = -1;
        v1[i] = 1;
        constraints.push_back(std::move(v));
        constraints.push_back(std::move(v1));
        constraints_B.push_back(-1);
        constraints_B.push_back(2);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> s >> d;
        cout << s << ' ' << d << ' ';
        VD C(idx), C1(idx);
        while (s != d) {
            int index = road_to_idx[make_pair(p[s][d], d)];
            C[index] = -AM[p[s][d]][d];
            C1[index] = AM[p[s][d]][d];
            d = p[s][d];
        }

        LPSolver solver(constraints, constraints_B, C);
        VD x;
        DOUBLE value = solver.Solve(x);
        LPSolver solver1(constraints, constraints_B, C1);
        DOUBLE value1 = solver1.Solve(x);
        cout << fixed << setprecision(6) << -value << ' ' << value1 << '\n';
    }
}