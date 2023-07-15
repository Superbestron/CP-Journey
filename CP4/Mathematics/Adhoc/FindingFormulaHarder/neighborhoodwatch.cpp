#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N, K, idx, streak = 0, ans = 0;
    cin >> N >> K;
    bool arr[N];
    memset(arr, false, sizeof arr);
    for (int i = 0; i < K; i++) {
        cin >> idx;
        arr[idx - 1] = true;
    }
    for (int i = 0; i < N; i++) {
        if (arr[i]) {
            ans += (streak + 1) * streak / 2;
            streak = 0;
        } else streak++;
    }
    ans += (streak + 1) * streak / 2;
    cout << (N + 1) * N / 2 - ans;
}