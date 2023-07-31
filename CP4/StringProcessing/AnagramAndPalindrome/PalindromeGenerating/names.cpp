#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string S;
    cin >> S;
    int N = S.size(), ans = N - 1;
    for (int i = N; i < N + N / 2; i++) {
        S += '-';
        int cur = 0;
        for (int j = 0; j < i / 2; j++) {
            if (S[j] != S[i - j - 1]) cur++;
        }
        ans = min(ans, cur);
    }
    cout << ans;
}