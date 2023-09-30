#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll fact[200001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    const ll MOD = 998244353;
    string s;
    cin >> t;
    fact[0] = 1;
    for (int i = 1; i <= 200000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    while (t--) {
        cin >> s;
        vector<ll> grps;
        char prev = ' ';
        int size = 0;
        for (char c : s) {
            if (c == prev) {
                size++;
            } else {
                if (prev != ' ') {
                    grps.push_back(size);
                }
                size = 1;
            }
            prev = c;
        }
        grps.push_back(size);
        ll mini = 0, sum = 1;
        for (ll i : grps) {
            mini += i - 1;
            if (i == 1) continue;
            sum = (sum * i) % MOD;
        }

        cout << mini << ' ' << (fact[mini] * sum) % MOD << '\n';
    }
}

