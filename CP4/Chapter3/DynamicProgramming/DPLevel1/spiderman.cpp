#include <bits/stdc++.h>

using namespace std;

int N, M, moves[40], memo[41][1001];

int dp(int left, int height) {
    if (left == M && height == 0) return 0;
    if (left == M || height < 0) return 2e9;
    int& ans = memo[left][height];
    if (ans != -1) return ans;
    ans = min(dp(left + 1, height + moves[left]),  dp(left + 1, height - moves[left]));
    return ans = max(height, ans);
}

void reconstruct(int left, int height) {
    if (left == M) return;
    int up = height + moves[left];
    int down = height - moves[left];
    if (dp(left + 1, down) <= dp(left + 1, up)) {
        cout << "D";
        reconstruct(left + 1, down);
    } else {
        cout << "U";
        reconstruct(left + 1, up);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    while (N--) {
        cin >> M;
        fill(memo[0], memo[0] + 41 * 1001, -1);
        for (int i = 0; i < M; i++) {
            cin >> moves[i];
        }
        dp(0, 0);
        if (memo[0][0] != 2e9) {
            reconstruct(0, 0);
            cout << '\n';
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }
}