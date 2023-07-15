#include <bits/stdc++.h>

using namespace std;

int findRowSize(int n) {
    int maxi = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) maxi = max(maxi, i);
    }
    return maxi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, ans; cin >> s;
    int rowSize = findRowSize(s.size());
    int colSize = s.size() / rowSize;
    int ctr = 0;
    char arr[rowSize][colSize];
    for (int j = 0; j < colSize; j++) {
        for (int i = 0; i < rowSize; i++) {
            arr[i][j] = s[ctr++];
        }
    }
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            ans += arr[i][j];
        }
    }
    cout << ans;
}