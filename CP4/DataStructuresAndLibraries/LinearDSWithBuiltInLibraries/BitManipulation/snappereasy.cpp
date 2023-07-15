#include <iostream>
#include <bitset>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k;
    bitset<10> arr;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k;
        while (k-- > 0) {
            int ctr = 0;
            while (ctr < n) {
                if (!arr[ctr]) {
                    arr[ctr++].flip();
                    break;
                }
                arr[ctr++].flip();
            }
        }
        cout << "Case #" << i << ": ";
        bool on = true;
        for (int j = 0; j < n; j++) {
            if (!arr[j]) {
                cout << "OFF" << endl;
                on = false;
                break;
            }
        }
        if (on) cout << "ON" << endl;
        arr.reset();
    }
}