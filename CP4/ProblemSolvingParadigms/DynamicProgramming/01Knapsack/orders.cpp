#include <bits/stdc++.h>

using namespace std;

vector<int> cost, ans;
long long memo[101][30001];
int n, c, m, s;

long long dp(int id, int val) {
    if (val == 0) return 1;
    if (id == n || val < 0) return 0;
    long long &ans = memo[id][val];
    if (ans != -1) return ans;
    return ans = dp(id + 1, val) + dp(id, val - cost[id]);
}

void reconstruct(int id, int val) {
    if (val == 0) return;
    if (dp(id + 1, val) == 1) {
        reconstruct(id + 1, val);
    } else {
        ans.push_back(id);
        reconstruct(id, val - cost[id]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < n; i++) {
        cin >> c;
        cost.push_back(c);
    }
    cin >> m;
    while (m--) {
        cin >> s;
        ans.clear();
        long long result = dp(0, s);
        if (result == 0) cout << "Impossible\n";
        else if (result > 1) cout << "Ambiguous\n";
        else {
            reconstruct(0, s);
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i] + 1 << ((i != (ans.size() - 1)) ? ' ' : '\n');
            }
        }
    }
}
