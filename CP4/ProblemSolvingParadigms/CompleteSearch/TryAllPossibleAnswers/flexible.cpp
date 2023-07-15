#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int W, P, temp; cin >> W >> P;
    vector<int> v;
    v.push_back(0);
    while (P--) {
        cin >> temp;
        v.push_back(temp);
    }
    v.push_back(W);
    set<int> s;
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = i + 1; j < v.size(); j++) {
            s.insert(v[j] - v[i]);
        }
    }
    for (int i : s) cout << i << ' ';
}