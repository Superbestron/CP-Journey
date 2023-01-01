#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, first, s, d; cin >> n;
    while (n--) {
        cin >> s >> d;
        first = s + d;
        if (first % 2 || s < first / 2) cout << "impossible" << endl;
        else cout << max(first / 2, s - first / 2) << ' ' << min(first / 2, s - first / 2) << endl;
    }
}