#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int R; cin >> R;
    string arr[R];
    unordered_set<char> sets[R];
    int permute[R], qc_arr[R][R];
    for (int i = 0; i < R; i++) {
        cin >> arr[i];
        unordered_set<char> s;
        for (char c : arr[i]) s.insert(c);
        sets[i] = s;
        permute[i] = i;
    }
    for (int i = 0; i < R; i++) {
        // finding difference between each pair of routines
        for (int j = 0; j < R; j++) {
            int qc = 0;
            for (char c : arr[j]) if (sets[i].count(c)) qc++;
            qc_arr[i][j] = qc;
        }
    }

    int min_qc = 9999;
    do {
        int curr_qc = 0;
        for (int i = 1; i < R; i++) {
            curr_qc += qc_arr[permute[i - 1]][permute[i]];
        }
        min_qc = min(min_qc, curr_qc);
    }
    while (next_permutation(permute, permute + R));
    cout << min_qc;
}
