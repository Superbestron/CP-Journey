#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, ctr = 0; cin >> n;
    vector<pair<int, int>> vect;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        vect.emplace_back(i, k);
    }
    while (vect.size() != 1) {
        ctr = (ctr + vect[ctr].second - 1) % vect.size();
        vect.erase(vect.begin() + ctr);
        ctr = ctr % vect.size();
    }
    cout << vect[0].first;

    return 0;
}