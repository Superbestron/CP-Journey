#include <bits/stdc++.h>

using namespace std;
using ii = tuple<int, int>;
vector<vector<ii>> AL;
priority_queue<ii, vector<ii>, greater<>> pq;
bool unsafe[10000];
int dist[10000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, A, K, T1, T2, D, B;
    while (cin >> N >> M >> A >> K && !(N == 0 && M == 0 && A == 0 && K == 0)) {
        AL.assign(N, vector<ii>());
        fill(dist, dist + 10000, 1e9);
        memset(unsafe, false, sizeof unsafe);
        for (int i = 0; i < M; i++) {
            cin >> T1 >> T2 >> D;
            T1--; T2--;
            AL[T1].emplace_back(T2, D);
            AL[T2].emplace_back(T1, D);
        }
        for (int i = 0; i < A; i++) {
            cin >> B; B--;
            dist[B] = 0;
            unsafe[B] = true;
            pq.emplace(dist[B], B);
            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d > dist[u]) continue;
                for (auto& [v, w] : AL[u]) {
                    if (d + w >= dist[v]) continue;
                    dist[v] = d + w;
                    if (dist[v] < K) unsafe[v] = true;
                    pq.emplace(dist[v], v);
                }
            }
            cout << N - accumulate(unsafe, unsafe + 10000, 0) << '\n';
        }
        cout << '\n';
    }
}