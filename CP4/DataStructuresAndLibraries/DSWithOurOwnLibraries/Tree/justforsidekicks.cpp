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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q, V[6], op, op1, op2; cin >> N >> Q;
    string gems;
    vector<FenwickTree> arr;
    for (int& i : V) {
        cin >> i;
        arr.emplace_back(N);
    }
    cin >> gems;
    for (int i = 0; i < gems.size(); i++) {
        arr[gems[i] - '1'].update(i + 1, 1);
    }
    while (Q--) {
        cin >> op >> op1 >> op2;
        if (op == 1) {
            arr[gems[op1 - 1] - '1'].update(op1, -1);
            // update gems string
            gems[op1 - 1] = (char) (op2 + '0');
            arr[op2 - 1].update(op1, 1);
        } else if (op == 2) {
            V[op1 - 1] = op2;
        } else {
            ll sum = 0;
            for (int i = 0; i < 6; i++) {
                sum += (ll) arr[i].rsq(op1, op2) * V[i];
            }
            cout << sum << '\n';
        }
    }
}
