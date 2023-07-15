#include <bits/stdc++.h>

using namespace std;

#define LSOne(S) ((S) & -(S))                    // the key operation

typedef long long ll;                            // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

class FenwickTree {                              // index 0 is not used
private:
    vll ft;                                        // internal FT is an array
public:
    explicit FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT

    ll rsq(int j) {                                // returns RSQ(1, j)
        ll sum = 0;
        for (; j; j -= LSOne(j))
            sum += ft[j];
        return sum;
    }

    ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion

    // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
    void update(int i, ll v) {
        for (; i < (int)ft.size(); i += LSOne(i))
            ft[i] += v;
    }

    int select(ll k) {                             // O(log m)
        int p = 1;
        while (p*2 < (int)ft.size()) p *= 2;
        int i = 0;
        while (p) {
            if (k > ft[i+p]) {
                k -= ft[i+p];
                i += p;
            }
            p /= 2;
        }
        return i+1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K, i, l, r; cin >> N >> K;
    char op;
    FenwickTree tree(N);
    while (K--) {
        cin >> op;
        if (op == 'F') {
            cin >> i;
            if (tree.rsq(i, i)) tree.update(i, -1);
            else tree.update(i, 1);
        } else {
            cin >> l >> r;
            cout << tree.rsq(l, r) << '\n';
        }
    }
}
