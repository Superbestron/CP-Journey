#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Number of blinks is still low enough to brute-force exactly what the question tells you to.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int val;
    vll v, v2;
    while (cin >> val) v.push_back(val);
    for (int times = 0; times < 25; times++) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == 0) {
                v2.push_back(1);
            } else if (to_string(v[i]).length() % 2 == 0) {
                string t = to_string(v[i]);
                int len = t.length();
                v2.push_back(stoll(t.substr(0, len / 2)));
                v2.push_back(stoll(t.substr(len / 2, len / 2)));
            } else {
                v2.push_back(v[i] * 2024);
            }
        }
        swap(v, v2);
        v2.clear();
    }
    cout << v.size() << '\n';
}
