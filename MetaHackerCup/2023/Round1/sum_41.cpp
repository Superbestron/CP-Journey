#include <bits/stdc++.h>
#include "../../../Libraries/PrimalityCheck.cpp"
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll T, P, sum;
vector<int> ans;

void primeFactors3(ll N) {                         // pre-condition, N >= 1
    vll factors;
    for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
        while (N%p[i] == 0) {                        // found a prime for N
            N /= p[i];                                 // remove it from N
            ans.push_back(p[i]);
            sum += p[i];
        }
    if (N != 1) {
        ans.push_back(N);              // remaining N is a prime
        sum += N;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    sieve(1000000);
    for (int i = 1; i <= T; i++) {
        cin >> P;
        sum = 0;
        ans.clear();
        primeFactors3(P);
        printf("Case #%d: ", i);
        if (sum > 41) {
            printf("%d\n", -1);
        } else {
            for (int j = sum; j < 41; j++) ans.push_back(1);
            cout << ans.size() << ' ';
            for (int &j : ans) cout << j << ' ';
            cout << '\n';
        }
    }
}
