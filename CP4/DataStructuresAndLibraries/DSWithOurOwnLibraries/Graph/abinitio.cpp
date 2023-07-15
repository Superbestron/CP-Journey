#include <bits/stdc++.h>

using namespace std;

bool AM[4000][4000];
int V;
long long modulo = 1e9 + 7;

// Key idea is to make transposing and complement operations cheap by "saving" the state of the graph
// instead of actually doing the transpose and complement operations

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(AM, false, sizeof AM);
    int E, Q, query, X, Y, A, B; cin >> V >> E >> Q;
    bool is_transposed = false, is_complement = false;
    while (E--) {
        cin >> A >> B;
        AM[A][B] = true;
    }
    while (Q--) {
        cin >> query;
        if (query == 1) {
            V++;
            if (is_complement) {
                for (int i = 0; i < V; i++){
                    AM[i][V - 1] = true;
                    AM[V - 1][i] = true;
                }
            }
        }
        else if (query == 2) {
            cin >> X >> Y;
            if (is_transposed && is_complement) AM[Y][X] = false;
            else if (is_transposed) AM[Y][X] = true;
            else if (is_complement) AM[X][Y] = false;
            else AM[X][Y] = true;
        } else if (query == 3) {
            cin >> X;
            if (is_complement) {
                for (int i = 0; i < V; i++) {
                    AM[X][i] = true;
                    AM[i][X] = true;
                }
            }
            else {
                for (int i = 0; i < V; i++) {
                    AM[X][i] = false;
                    AM[i][X] = false;
                }
            }
        } else if (query == 4) {
            cin >> X >> Y;
            if (is_transposed && is_complement) AM[Y][X] = true;
            else if (is_transposed) AM[Y][X] = false;
            else if (is_complement) AM[X][Y] = true;
            else AM[X][Y] = false;
        } else if (query == 5) is_transposed ^= true;
        else is_complement ^= true;
    }
    cout << V << '\n';
    for (int i = 0; i < V; i++) {
        long long multiplier = 1, sum = 0, outdegree = 0;
        for (int j = 0; j < V; j++) {
            if (i == j) continue;
            if (is_transposed && is_complement) {
                if (!AM[j][i]) {
                    sum = (sum + (multiplier * j) % modulo) % modulo;
                    outdegree++;
                    multiplier = (multiplier * 7) % modulo;
                }
            } else if (is_transposed) {
                if (AM[j][i]) {
                    sum = (sum + (multiplier * j) % modulo) % modulo;
                    outdegree++;
                    multiplier = (multiplier * 7) % modulo;
                }
            } else if (is_complement) {
                if (!AM[i][j]) {
                    sum = (sum + (multiplier * j) % modulo) % modulo;
                    outdegree++;
                    multiplier = (multiplier * 7) % modulo;
                }
            } else {
                if (AM[i][j]) {
                    sum = (sum + (multiplier * j) % modulo) % modulo;
                    outdegree++;
                    multiplier = (multiplier * 7) % modulo;
                }
            }
        }
        cout << outdegree << ' ' << sum << '\n';
    }
}