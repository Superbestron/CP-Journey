#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, g, val, start;
    cin >> n;
    while (n--) {
        cin >> g;
        cin >> start;
        for (int i = 1; i < g; i++) {
            cin >> val;
            if (val != ++start) {
                cout << i + 1 << endl;
                // ignore rest of input
                for (int j = i + 1; j < g; j++) cin >> val;
                break;
            }
        }
    }
}