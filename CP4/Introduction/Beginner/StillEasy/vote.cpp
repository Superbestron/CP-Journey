#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, val; cin >> t;
    while (t--) {
        cin >> n;
        int sum = 0, maxi = 0, winners = 0, idx;
        for (int i = 0; i < n; i++) {
            cin >> val;
            if (val > maxi) {
                idx = i;
                maxi = val;
                winners = 1;
            } else if (val == maxi) winners++;
            sum += val;
        }
        if (winners > 1) cout << "no winner" << endl;
        else {
            if (2 * maxi > sum) cout << "majority";
            else cout << "minority";
            cout << " winner " <<  idx + 1 << endl;
        }
    }
}