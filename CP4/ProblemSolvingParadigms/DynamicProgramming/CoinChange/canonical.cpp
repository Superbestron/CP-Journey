#include <bits/stdc++.h>

using namespace std;

unsigned long long memo[2000000];
long long n, coins[100], greedy[2000000];

long long greedy_dp(long long value) {
    if (value == 0) return 0;
    long long &ans = greedy[value];
    if (ans != -1) return ans;
    for (int i = n - 1; i >= 0; i--) {
        if (value - coins[i] >= 0) {
            return ans = 1 + greedy_dp(value - coins[i]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int second_maxi, maxi;
    cin >> n;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
        pq.push(coins[i]);
        if (pq.size() > 2) {
            pq.pop();
        }
    }
    maxi = pq.top(); pq.pop();
    second_maxi = pq.top();
    int limit = maxi + second_maxi;
    memset(memo, -1, sizeof memo);
    memset(greedy, -1, sizeof greedy);
    memo[0] = 0;
    for (int i = 0; i < limit; i++) {
        for (int j = 0; j < n; j++) {
            if (i + coins[j] < limit) memo[i + coins[j]] = min(memo[i + coins[j]], memo[i] + 1);
        }
    }
    for (int i = limit - 1; i >= 0; i--) {
        greedy_dp(i);
    }
    for (int i = 1; i < limit; i++) {
        if (memo[i] != greedy[i]) {
            cout << "non-canonical";
            return 0;
        }
    }
    cout << "canonical";
}
