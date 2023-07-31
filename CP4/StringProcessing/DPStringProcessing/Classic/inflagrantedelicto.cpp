#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, val, k = 0;
    cin >> N;
    int D[N], P[N];
    vector<int> L(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> val;
        val--;
        D[val] = i;
    }
    for (int i = 0; i < N; i++) {
        cin >> val;
        val--;
        P[i] = D[val];
    }
    for (int i = 0; i < N; i++) {
        int pos = lower_bound(L.begin(), L.begin() + k, P[i]) - L.begin();
        L[pos] = P[i];
        if (pos == k) k = pos + 1;
    }
    cout << 2 << ' ' << k + 1;
}