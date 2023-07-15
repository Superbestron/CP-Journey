#include <bits/stdc++.h>

using namespace std;

int n, temp;
long long complement = 0;
vector<int> fruits;

// number of subsets of fruits < 200 is much less than that of >= 200. Max of 3 fruits per basket.

void backtrack(int idx, int current_weight) {
    if (idx == n) {
        complement += current_weight;
        return;
    }

    if (current_weight + fruits[idx] < 200) backtrack(idx + 1, current_weight + fruits[idx]);
    backtrack(idx + 1, current_weight);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        fruits.push_back(temp);
    }

    backtrack(0, 0);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        // each fruit appears in 2^(n-1) baskets
        ans += fruits[i] * (1LL << (n - 1));
    }

    cout << ans - complement;
}