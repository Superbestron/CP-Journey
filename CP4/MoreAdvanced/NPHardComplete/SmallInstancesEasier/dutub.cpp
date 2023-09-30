#include <bits/stdc++.h>
using namespace std;

int n, t, cost = INT32_MAX, char_ctr = 0;
string s;
vector<int> costs;
vector<long long> masks;

void backtrack(int u, long long mask, int c) {
    if (mask == ((1 << char_ctr) - 1)) {
        cost = min(cost, c);
        return;
    }
    if (u == n) return;
    backtrack(u + 1, mask, c);
    // use u
    // only use if it covers something else
    while ((mask | masks[u]) == mask) u++;
    if (u < n) backtrack(u + 1, mask | masks[u], c + costs[u]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    masks.assign(n, 0);
    costs.assign(n, 0);
    unordered_map<char, int> char_to_int;
    for (int i = 0; i < n; i++) {
        cin >> t >> s;
        long long m = 0;
        for (char c : s) {
            if (!char_to_int.count(c)) {
                char_to_int[c] = char_ctr++;
            }
            m |= (1 << char_to_int[c]);
        }
        masks[i] = m;
        costs[i] = t;
    }
    backtrack(0, 0, 0);
    cout << cost;
}

