#include <bits/stdc++.h>

using namespace std;

int n;
int arr[2][1000000];

// remove all weights <= weight
bool can(int weight) {
    int ctr = 0, curr_weight = -1;
    for (auto& i : arr) {
        for (int j = 0; j < n; j++) {
            if (i[j] <= weight) continue;
            if (i[j] != curr_weight) {
                if (ctr == 0) { // to handle edge case at the start
                    curr_weight = i[j];
                    ctr++;
                } else return false;
            } else ctr = 0;
        }
        if (ctr == 1) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int max_weight = 0; cin >> n;
    for (auto& i : arr) {
        for (int j = 0; j < n; j++) {
            cin >> i[j];
            max_weight = max(max_weight, i[j]);
        }
    }

    int lo = 0, hi = max_weight;
    while (hi > lo) {
        int mid = (lo + hi) / 2;
        can(mid) ? hi = mid : lo = mid + 1;
    }
    cout << hi;
}