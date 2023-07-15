#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n;
    while (n--) {
        cin >> m;
        int A[m];
        for (int i = 0; i < m; i++) cin >> A[i];
        bool p = true;
        bool a = true;
        int d = A[1] - A[0];
        for (int i = 0; i < m - 1; i++) if (A[i + 1] - A[i] != d) p = false;
        sort(A, A + m);
        d = A[1] - A[0];
        for (int i = 0; i < m - 1; i++) if (A[i + 1] - A[i] != d) a = false;
        if (p) cout << "arithmetic" << '\n';
        else if (a) cout << "permuted arithmetic" << '\n';
        else cout << "non-arithmetic" << '\n';
    }
}