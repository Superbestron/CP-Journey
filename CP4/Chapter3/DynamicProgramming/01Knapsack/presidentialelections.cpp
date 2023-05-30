#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> states;
int memo[2017][2017];

int dp(int i, int needed) {
    if (needed <= 0) return 0;
    if (i == states.size()) return 1e9;
    int &ans = memo[i][needed];
    if (ans != -1) return ans;

    ans = min(dp(i + 1, needed), dp(i + 1, needed - states[i].first) + states[i].second);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int s, d, c, f, u, delegates = 0, curr_won = 0, unwon = 0;
    cin >> s;
    for (int i = 0; i < s; i++) {
        cin >> d >> c >> f >> u;
        delegates += d;
        // auto lose
        if (c + u <= f) {
            continue;
        }
        // auto win
        if (f + u < c) {
            curr_won += d;
            continue;
        }
        f += u;
        int weight = 1 + (c + f) / 2 - c;
//        cout << weight << '\n';
        states.emplace_back(d, weight);
        unwon += d;
    }
    c = curr_won;
    u = unwon;
    f = delegates - c - u;

    if (c + u <= f) {
        cout << "impossible\n";
        return 0;
    }
    // auto win
    if (f + u < c) {
        cout << 0 << '\n';
        return 0;
    }

    f += u;
    int weights = 1 + (c + f) / 2 - c;
    memset(memo, -1, sizeof memo);
    cout << dp(0, weights);
}
