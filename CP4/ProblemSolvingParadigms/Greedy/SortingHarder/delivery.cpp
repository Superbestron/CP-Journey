#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K, x, t, extra_to_deliver = 0, ans = 0; cin >> N >> K;
    vector<pair<int, int>> left, right;
    while (N--) {
        cin >> x >> t;
        if (x < 0) left.emplace_back(-x, t);
        else right.emplace_back(x, t);
    }
    sort(left.begin(), left.end(), greater());
    sort(right.begin(), right.end(), greater());
    for (auto& p : left) {
        int letters = p.second;
        letters -= extra_to_deliver;
        int trips = ceil(letters * 1.0 / K);
        ans += trips * p.first * 2;
        extra_to_deliver = trips * K - letters;
    }
    extra_to_deliver = 0;
    for (auto& p : right) {
        int letters = p.second;
        letters -= extra_to_deliver;
        int trips = ceil(letters * 1.0 / K);
        ans += trips * p.first * 2;
        extra_to_deliver = trips * K - letters;
    }
    cout << ans;
}