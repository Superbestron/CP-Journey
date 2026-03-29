#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;

// Pretty simple compared to the monster of a question of 21. Abridged question: Find the 4-numbered sequence that nets
// you the most bananas given x series of secret numbers. HashMaps are extremely useful here to only record down the
// number of bananas when a 4-numbered sequence is first encountered in a particular series of secret numbers.

constexpr ll MOD = 16777216;

void process(ll& num) {
    num ^= num * 64;
    num %= MOD;
    num ^= num / 32;
    num %= MOD;
    num ^= num * 2048;
    num %= MOD;
}

iiii can(queue<ll>& q) {
    ll a = q.front(); q.pop();
    ll b = q.front(); q.pop();
    ll c = q.front(); q.pop();
    ll d = q.front(); q.pop();
    q.push(a);
    q.push(b);
    q.push(c);
    q.push(d);
    return {a, b, c, d};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll num;
    map<iiii, ll> global;
    set<ll> ans;
    while (cin >> num) {
        ll prev = num % 10;
        queue<ll> q;
        set<iiii> mp;
        for (int i = 0; i < 2000; i++) {
            process(num);
            const ll ones = num % 10;
            q.push(ones - prev);
            prev = ones;
            if (q.size() == 4) {
                iiii tup = can(q);
                q.pop();
                if (mp.contains(tup)) continue;
                mp.insert(tup);
                global[tup] += ones;
            }
        }
    }
    for (auto &[k, v]: global) ans.insert(v);
    cout << *prev(ans.end()) << '\n';
}
