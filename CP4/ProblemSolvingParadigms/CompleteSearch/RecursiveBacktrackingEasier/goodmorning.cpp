#include <bits/stdc++.h>

using namespace std;

vector<int> adjlist[10];

int backtrack(int n, int pos, int cur_val) {
    if (cur_val >= n) return cur_val;
    if (cur_val == 0 && pos == 0) return 0;
    int best = cur_val;
    int smallest_difference = n - cur_val;
    for (int i : adjlist[pos]) {
        int new_val;
        if (i == pos) new_val = backtrack(n, pos, cur_val * 10 + i);
        else new_val = backtrack(n, i, cur_val);
        int new_difference = abs(new_val - n);
        if (new_difference < smallest_difference) {
            smallest_difference = new_difference;
            best = new_val;
        }
    }
    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    adjlist[0] = {0};
    adjlist[1] = {1, 4, 2};
    adjlist[2] = {2, 3, 5};
    adjlist[3] = {3, 6};
    adjlist[4] = {4, 5, 7};
    adjlist[5] = {5, 6, 8};
    adjlist[6] = {6, 9};
    adjlist[7] = {7, 8};
    adjlist[8] = {8, 0, 9};
    adjlist[9] = {9};
    int T, k; cin >> T;
    while (T--) {
        cin >> k;
        cout << backtrack(k, 1, 0) << '\n';
    }
}