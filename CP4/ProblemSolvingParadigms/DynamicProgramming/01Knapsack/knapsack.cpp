#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> vect;
vector<int> ans;

// reconstruct
void reconstruct(vector<vector<int>>& dp, int i, int w) {
    if (i == 0) return;
    // if score is higher if we take item i, it means we have taken item i
    if (dp[i][w] > dp[i - 1][w]) {
        ans.push_back(i - 1);
        reconstruct(dp, i - 1, w - vect[i - 1].second);
    } else {
        reconstruct(dp, i - 1, w);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    string s, t1, t2;
    int C, n, v, w;
    while (getline(cin, s)) {
        istringstream str(s);
        str >> t1 >> t2;
        C = stoi(t1); n = stoi(t2);
        vect.clear();
        for (int i = 0; i < n; i++) {
            cin >> v >> w;
            vect.emplace_back(v, w);
        }
        cin.ignore();
        vector<vector<int>> dp(n + 1, vector<int>(C + 1));
        for (int i = 0; i <= n; i++) {
            for (int weight = 0; weight <= C; weight++) {
                if (i == 0 || weight == 0)
                    dp[i][weight] = 0;
                else if (vect[i - 1].second <= weight)
                    dp[i][weight] = max(vect[i - 1].first + dp[i - 1][weight - vect[i - 1].second], dp[i - 1][weight]);
                else
                    dp[i][weight] = dp[i - 1][weight];
            }
        }
        ans.clear();
        reconstruct(dp, n, C);
        cout << ans.size() << '\n';
        for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] << ' ';
        cout << '\n';
    }
}
