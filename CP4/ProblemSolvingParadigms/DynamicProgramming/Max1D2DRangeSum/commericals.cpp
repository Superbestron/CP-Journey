#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p, maxi = 0, curr = 0, val;
    cin >> n >> p;
    for (int i = 0; i < n; i++) {
        cin >> val;
        val -= p;
        curr += val;
        if (curr < 0) curr = 0;
        maxi = max(maxi, curr);
    }
    cout << maxi;
}