#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, n, val; cin >> r >> n;
    bool arr[r]; memset(arr, false, sizeof arr);
    while (n--) {
        cin >> val;
        arr[val - 1] = true;
    }
    for (int i = 0; i < r; i++) {
        if (!arr[i]) {
            cout << i + 1;
            return 0;
        }
    }
    cout << "too late";
}