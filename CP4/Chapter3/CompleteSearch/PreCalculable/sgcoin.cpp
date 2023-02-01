#include <bits/stdc++.h>

using namespace std;

int mod = 1e7;

long long H(long long previousHash, string &transaction, long long token) {
    long long v = previousHash;
    for (char i : transaction) v = (v * 31 + i) % 1000000007;
    return (v * 7 + token) % 1000000007;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long h; cin >> h;
    string a = "a", b = "b";
    long long token = 0, hash = 1;
    while (hash % mod) {
        hash = H(h, a, token++);
    }
    cout << a << ' ' << token - 1 << '\n';
    token = 0;
    h = hash; hash = 1;
    while (hash % mod) {
        hash = H(h, b, token++);
    }
    cout << b << ' ' << token - 1 << '\n';
}
