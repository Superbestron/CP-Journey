#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, B;
    while (cin >> N >> B && N != -1 && B != -1) {
        priority_queue<tuple<double, int, int>> pq;
        for (int i = 0; i < N; i++) {
            int a; cin >> a;
            pq.emplace(static_cast<double>(a / 1.0), a, 1);
        }
        B -= N;
        while (B--) {
            auto [r, num, den] = pq.top(); pq.pop();
            pq.emplace(num / (den + 1.0), num, den + 1);
        }
        cout << ceil(get<0>(pq.top())) << '\n';
    }
}