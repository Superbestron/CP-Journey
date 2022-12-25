#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int n, count = 1, val;
    while (cin >> n) {
        int mini = 1000000, maxi = -1000000;
        for (int i = 0; i < n; i++) {
            cin >> val;
            mini = min(mini, val);
            maxi = max(maxi, val);
        }
        cout << "Case " << count++ << ": " << mini << ' ' << maxi << ' ' << maxi - mini << endl;
    }
}