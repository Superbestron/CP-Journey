#include <iostream>
#include <vector>

using namespace std;

long long memo[100001];

int main() {
    ios_base::sync_with_stdio(false);
    int T,L;
    cin>>T;
    for (int t = 1; t <= T; t++) {
        fill(memo, memo + 100001, 999999);
        cin>>L;
        memo[1] = 1;
        for (int i = 1; i <= L; i++) {
            if (i + 1 <= L) {
                memo[i+1] = min(memo[i] + 1, memo[i+1]);
            }
            int ctr = i * 2, cost = 6;
            while (ctr <= L) {
                memo[ctr] = min(cost + memo[i], memo[ctr]);
                ctr += i;
                cost += 2;
            }
            // cout << memo[i] << endl;
        }


        cout << "Case #" << t << ": " << memo[L] << '\n';
    }
}

