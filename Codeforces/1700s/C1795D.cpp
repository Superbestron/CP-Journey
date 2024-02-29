#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
typedef long long ll;
vector<ll> fact;

ll powmod(ll a, ll b) {
    a %= MOD;
    if (a == 0) return 0;
    ll product = 1;
    while (b > 0) {
        if (b & 1) {
            product *= a;
            product %= MOD;
            --b;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return product;
}

ll inv(ll a) {
    return powmod(a, MOD - 2);
}

ll nCk(ll n, ll k) {
    return ((fact[n] * inv(fact[k]) % MOD) * inv(fact[n - k])) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long ans = 1;
    cin >> n;
    fact.assign(n + 1, 1);
    for (int i = 2; i <= n; i++) fact[i] = (i * fact[i - 1]) % MOD;
    for (int i = 0; i < n / 3; i++) {
        int arr[3];
        for (int& j : arr) cin >> j;
        sort(arr, arr + 3);
        if (arr[0] == arr[1] && arr[0] == arr[2]) ans *= 3;
        else if (arr[0] == arr[1]) ans *= 2;
        ans %= MOD;
    }
    ll x = nCk(n / 3, n / 6);
    cout << (ans * x) % MOD;
}