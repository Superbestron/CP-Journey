#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, n, m, u, v, d, z, a, b, c;
    cin >> n >> k >> m;
    vector<int> people(13);
    // vector of [start, end, capacity]
    unordered_map<int, vector<vector<int>>> flights;
    unordered_map<int, vector<pair<int,int>>> additional;
    while (m--) {
        cin >> u >> v >> d >> z;
        flights[d].push_back({u, v, z});
    }
    for (int i = 0; i < k * n; i++) {
        cin >> a >> b >> c;
        additional[b].emplace_back(a, c);
    }
    for (int i = 1; i <= n; i++) {
        for (auto& vect : additional[i]) {
            people[vect.first] += vect.second;
        }
        for (auto& vect : flights[i]) {
            people[vect[0]] -= vect[2];
            if (people[vect[0]] < 0) {
                cout << "suboptimal";
                return 0;
            }
        }
        for (auto& vect : flights[i]) {
            people[vect[1]] += vect[2];
        }
    }

    cout << "optimal";
}