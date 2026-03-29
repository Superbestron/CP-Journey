#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Implement as it is.

const ll MOD = 16777216;

void process(ll& num) {
    num ^= num * 64;
    num %= MOD;
    num ^= num / 32;
    num %= MOD;
    num ^= num * 2048;
    num %= MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll num, ans = 0;
    while (cin >> num) {
        for (int i = 0; i < 2000; i++) process(num);
        ans += num;
    }
    cout << ans << '\n';
}
