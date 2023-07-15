#include <bits/stdc++.h>

using namespace std;

vector<int> p, A(200);

void print_LIS(int i) {
    if (p[i] == -1) {
        cout << A[i] << ' ';
        return;
    }
    print_LIS(p[i]);
    cout << A[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        int k = 0, lis_end = 0;
        vector<int> L(n), L_id(n);
        p.assign(n, -1);

        for (int i = 0; i < n; i++) {
            int pos = lower_bound(L.begin(), L.begin() + k, A[i]) - L.begin();
            L[pos] = A[i];
            L_id[pos] = i;
            p[i] = pos ? L_id[pos - 1] : -1;
            if (pos == k - 1) lis_end = i;
            else if (pos == k) {
                k = pos + 1;
                lis_end = i;
            }
        }
        cout << k << ' ';
        print_LIS(lis_end);
        cout << '\n';
    }
}
