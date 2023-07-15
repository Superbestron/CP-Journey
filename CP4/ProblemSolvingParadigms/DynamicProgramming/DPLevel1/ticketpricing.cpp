#include <bits/stdc++.h>

using namespace std;

int N, W, K, min_price = 2e9, prices[53][1000], tickets[53][300], memo[54][301], choices[53];

int dp(int weeks, int seats) {
    if (weeks == W || seats == 0) return 0;
    int& ans = memo[weeks][seats];
    if (ans != -1) return ans;
    ans = 0;
    for (int i = 0; i < choices[weeks]; i++) {
        int can_seat = min(seats, tickets[weeks][i]);
        ans = max(ans, can_seat * prices[weeks][i] + dp(weeks + 1, seats - can_seat));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> W;
    fill(memo[0], memo[0] + 54 * 301, -1);
    W++;
    for (int i = 0; i < W; i++) {
        cin >> K;
        choices[i] = K;
        for (int j = 0; j < K; j++) cin >> prices[i][j];
        for (int j = 0; j < K; j++) cin >> tickets[i][j];
    }
    cout << dp(0, N) << '\n';
    for (int i = 0; i < choices[0]; i++) {
        int can_seat = min(N, tickets[0][i]);
        if (memo[0][N] == can_seat * prices[0][i] + dp(1, N - can_seat)) {
            min_price = min(min_price, prices[0][i]);
        }
    }
    cout << min_price;
}