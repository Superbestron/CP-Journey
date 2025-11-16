#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Bounds are low enough to brute force every possible combination to reach the prize.

pair<int, int> parse(string& s) {
    vector<string> t = split(s, ':');
    vector<string> t2 = split(t[1], ',');
    int a1 = stoi(split(t2[0], '+')[1]);
    int a2 = stoi(split(t2[1], '+')[1]);
    return {a1, a2};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int ans = 0;
    vector<string> grid;
    while (getline(cin, s)) {
        auto [a1, a2] = parse(s);
        getline(cin, s);
        auto [b1, b2] = parse(s);
        getline(cin, s);
        vector<string> t = split(s, ':');
        vector<string> t2 = split(t[1], ',');
        int p1 = stoi(split(t2[0], '=')[1]);
        int p2 = stoi(split(t2[1], '=')[1]);
        vi pref_a1, pref_a2, pref_b1, pref_b2;
        for (int i = 0; i <= 100; i++) {
            pref_a1.push_back(a1 * i);
            pref_a2.push_back(a2 * i);
            pref_b1.push_back(b1 * i);
            pref_b2.push_back(b2 * i);
        }
        int mn = INT_MAX;
        for (int i = 0; i <= 100; i++) {
            for (int j = 0; j <= 100; j++) {
                int x_sum = pref_a1[i] + pref_b1[j];
                int y_sum = pref_a2[i] + pref_b2[j];
                int cost = 3 * i + j;
                if (x_sum == p1 && y_sum == p2) {
                    mn = min(cost, mn);
                }
            }
        }
        if (mn != INT_MAX) ans += mn;
        getline(cin, s);
    };
    cout << ans << '\n';
}
